#!/usr/bin/env python3
"""Random source permuter for near-miss functions: rewrites one function in small, behaviour-preserving-ish ways,
compiles each variant with mwccarm and keeps the variants whose machine code is closer to the ROM.

usage: permuter.py FILE FUNCTION [-n ITERATIONS] [-j WORKERS] [-o OUT] [--seed N]
  FILE      a draft .cpp that compiles (put it in your scratch folder, never in src/wip)
  FUNCTION  the definition name as written in FILE (plain name, Class::method or the mangled name)
The best variant is written to OUT (default FILE with .best.cpp) whenever the score improves; score 0 is a match.
Score: differing instruction words (relocations masked) + 4 per missing/extra word. A variant that does not compile
is discarded. Mutations: swap adjacent declarations, swap adjacent simple statements, change a local's integer type
(s32/u32/int, s16/u16, s8/u8), flip commutative operands (+ * & | ^ == !=), `x != 0` <-> `x`, and add or remove a
temporary for a call result. Every result must still be checked by hand (trymatch, check_sizes) before use.
"""
import argparse, multiprocessing as mp, random, re, subprocess, sys, tempfile
from pathlib import Path

ROOT = Path(__file__).parent.parent
sys.path.insert(0, str(ROOT / "tools"))
from trymatch import DEFAULT_FLAGS, name_to_addr, call_mismatches  # noqa: E402
from sdk_sigmatch import extract_functions  # noqa: E402
import defs  # noqa: E402

CC = ROOT / "tools/mwccarm/dsi/1.2/mwccarm.exe"
DATA = (ROOT / "extract/eur/arm9/arm9.bin").read_bytes()
BASE = 0x02004000
TYPES = [("s32", "u32", "int"), ("s16", "u16"), ("s8", "u8")]
DECL = re.compile(r"^(\s+)((?:const\s+)?(?:unsigned\s+)?[A-Za-z_]\w*\s*\**)\s*(\w+)(\s*=.*)?;\s*(//.*)?$")
SIMPLE = re.compile(r"^\s+[^{}]*;\s*(//.*)?$")
CONTROL = re.compile(r"^\s*(if|else|for|while|do|switch|case|default|return|break|continue|goto)\b")


def function_span(lines, name):
    for i, n in defs.def_starts(lines):
        if n == name or n.split("::")[-1] == name.split("::")[-1]:
            depth, j, seen = 0, i, False
            while j < len(lines):
                depth += lines[j].count("{") - lines[j].count("}")
                seen = seen or "{" in lines[j]
                if seen and depth == 0:
                    return i, j
                j += 1
    sys.exit(f"{name} not found")


def score(text, target_addr, workdir):
    src = Path(workdir) / "v.cpp"
    obj = Path(workdir) / "v.o"
    src.write_text(text, encoding="utf-8")
    if obj.exists():
        obj.unlink()
    cmd = f'"{CC}" {DEFAULT_FLAGS} -lang=c++ -i "{ROOT / "include"}" -i "{ROOT}" -c "{src}" -o "{obj}"'
    if subprocess.run(cmd, shell=True, capture_output=True).returncode != 0 or not obj.exists():
        return None
    raw = obj.read_bytes()
    bad_calls = call_mismatches(raw, DATA, BASE)
    for name, thumb, code, mask in extract_functions(raw):
        if name_to_addr(name) != target_addr:
            continue
        off = target_addr - BASE
        want = DATA[off:off + len(code) + 64]
        s = 0
        for k in range(0, len(code), 4):
            a, b, m = want[k:k + 4], code[k:k + 4], mask[k:k + 4]
            if any((x ^ y) & z for x, y, z in zip(a, b, m)):
                s += 1
        # the original function's length: the next symbol in the ROM is not known here, so penalise a size change
        # through the caller's reference size
        s += 4 * abs(len(code) - REF_SIZE) // 4
        s += 2 * len(bad_calls.get(name, []))
        return s
    return None


def mutate(lines, lo, hi, rng):
    body = list(range(lo + 1, hi))
    kind = rng.randrange(7)
    out = list(lines)
    if kind == 0:  # swap adjacent declarations
        ds = [i for i in body if DECL.match(out[i]) and DECL.match(out[i + 1] if i + 1 < hi else "")]
        if ds:
            i = rng.choice(ds)
            out[i], out[i + 1] = out[i + 1], out[i]
            return out
    if kind == 1:  # swap adjacent simple statements at the same indent
        ss = [i for i in body if i + 1 < hi and SIMPLE.match(out[i]) and SIMPLE.match(out[i + 1])
              and not CONTROL.match(out[i]) and not CONTROL.match(out[i + 1]) and not DECL.match(out[i])
              and not DECL.match(out[i + 1])
              and len(out[i]) - len(out[i].lstrip()) == len(out[i + 1]) - len(out[i + 1].lstrip())]
        if ss:
            i = rng.choice(ss)
            out[i], out[i + 1] = out[i + 1], out[i]
            return out
    if kind == 2:  # change a local's integer type
        ds = [i for i in body if DECL.match(out[i])]
        rng.shuffle(ds)
        for i in ds:
            m = DECL.match(out[i])
            t = m.group(2).strip()
            for group in TYPES:
                if t in group:
                    alt = rng.choice([g for g in group if g != t])
                    out[i] = out[i].replace(t, alt, 1)
                    return out
    if kind == 3:  # flip operands of a commutative operator with simple operands
        cand = [i for i in body if re.search(r"\b\w+(?:->\w+|\.\w+|\[\w+\])?\s*(\+|\*|&|\||\^|==|!=)\s*\w+(?:->\w+|\.\w+|\[\w+\])?\b", out[i])]
        if cand:
            i = rng.choice(cand)
            ms = list(re.finditer(r"(?<![\w>.\]])(\w+(?:->\w+|\.\w+|\[\w+\])?)\s*(\+|\*|&|\||\^|==|!=)\s*(\w+(?:->\w+|\.\w+|\[\w+\])?)(?![\w(\[])", out[i]))
            ms = [m for m in ms if not (m.group(2) in "&*" and m.start() > 0 and out[i][m.start() - 1] in "(,=")]
            if ms:
                m = rng.choice(ms)
                out[i] = out[i][:m.start()] + f"{m.group(3)} {m.group(2)} {m.group(1)}" + out[i][m.end():]
                return out
    if kind == 4:  # x != 0  <->  x  inside conditions
        cand = [i for i in body if re.search(r"\b(if|while)\s*\(", out[i])]
        if cand:
            i = rng.choice(cand)
            if " != 0)" in out[i]:
                out[i] = out[i].replace(" != 0)", ")", 1)
            else:
                out[i] = re.sub(r"\(\s*(\w+(?:->\w+|\.\w+)?)\s*\)", r"(\1 != 0)", out[i], count=1)
            return out
    if kind == 5:  # move a declaration to another place among the declarations
        ds = [i for i in body if DECL.match(out[i]) and not DECL.match(out[i]).group(4)]
        if len(ds) > 1:
            a, b = rng.sample(ds, 2)
            line = out.pop(a)
            out.insert(b, line)
            return out
    if kind == 6:  # swap two statements two apart (both simple, same indent)
        ss = [i for i in body if i + 2 < hi and all(SIMPLE.match(out[k]) and not CONTROL.match(out[k])
                                                   and not DECL.match(out[k]) for k in (i, i + 1, i + 2))]
        if ss:
            i = rng.choice(ss)
            out[i], out[i + 2] = out[i + 2], out[i]
            return out
    return None


def worker(args):
    text, name, addr, iters, seed, start_score = args
    rng = random.Random(seed)
    lines = text.split("\n")
    best, best_lines = start_score, lines
    cur, cur_lines = start_score, lines
    with tempfile.TemporaryDirectory() as wd:
        for _ in range(iters):
            lo, hi = function_span(cur_lines, name)
            new = mutate(cur_lines, lo, hi, rng)
            if new is None:
                continue
            s = score("\n".join(new), addr, wd)
            if s is None:
                continue
            if s <= cur or rng.random() < 0.02:  # accept equal or better, rarely worse (to leave plateaus)
                cur, cur_lines = s, new
                if s < best:
                    best, best_lines = s, new
                    if s == 0:
                        break
    return best, "\n".join(best_lines)


def main():
    global REF_SIZE
    ap = argparse.ArgumentParser()
    ap.add_argument("file", type=Path)
    ap.add_argument("function")
    ap.add_argument("-n", type=int, default=400, help="iterations per worker per round")
    ap.add_argument("-j", type=int, default=4, help="parallel workers")
    ap.add_argument("-r", type=int, default=5, help="rounds (each restarts the workers from the best so far)")
    ap.add_argument("-o", type=Path)
    ap.add_argument("--seed", type=int, default=1)
    args = ap.parse_args()
    out = args.o or args.file.with_suffix(".best.cpp")
    text = args.file.read_text(encoding="utf-8")
    addr = name_to_addr(args.function.replace("::", "_"))
    if addr is None:
        sys.exit(f"no address for {args.function}")
    import re as _re
    for l in (ROOT / "config/eur/arm9/symbols.txt").read_text().splitlines():
        m = _re.search(r"size=0x([0-9a-f]+)\) addr:0x([0-9a-f]+)", l)
        if m and int(m.group(2), 16) == addr:
            REF_SIZE = int(m.group(1), 16)
            break
    else:
        sys.exit("size not found in symbols.txt")
    with tempfile.TemporaryDirectory() as wd:
        best = score(text, addr, wd)
    if best is None:
        sys.exit("the input does not compile")
    print(f"start score {best}", flush=True)
    best_text = text
    for r in range(args.r):
        jobs = [(best_text, args.function, addr, args.n, args.seed * 1000 + r * 100 + k, best) for k in range(args.j)]
        with mp.Pool(args.j, initializer=_init, initargs=(REF_SIZE,)) as pool:
            results = pool.map(worker, jobs)
        s, t = min(results, key=lambda x: x[0])
        if s < best:
            best, best_text = s, t
            out.write_text(best_text, encoding="utf-8", newline="\n")
        print(f"round {r + 1}: best score {best}", flush=True)
        if best == 0:
            print(f"MATCH: written to {out}")
            return
    print(f"best score {best}; best variant in {out}" if best_text != text else "no improvement")


def _init(size):
    global REF_SIZE
    REF_SIZE = size


REF_SIZE = 0
if __name__ == "__main__":
    main()
