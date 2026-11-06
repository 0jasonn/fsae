#!/usr/bin/env python3
"""One-off: renames source files and headers whose names carry an implementer letter (textrender_e2.cpp,
lobby_e_4.cpp, knifecomm_f.cpp, ...) to plain module names. Sources get the module name or the next free _N;
a header goes to <module>.h (or <module>_api.h) when free, otherwise its body is appended to the existing one.
Include lines, delinks.txt and scratch/merge_failed.txt are rewritten. usage: drop_letters.py [--dry]"""
import re, subprocess, sys
from pathlib import Path
ROOT = Path(__file__).parent.parent
DRY = "--dry" in sys.argv
LETTER = re.compile(r"^(?P<base>.+?)_(?:e2|[a-g])(?:_(?P<n>\d+))?$")
SKIP = re.compile(r"^(pane|res_chunk|stub_noop|stub_zero|stub_empty|decls|objdecls|setcommon|common|rect)")


def taken(name):
    return any(p for p in (ROOT / "src").rglob(name) if "wip" not in p.parts)


moves = {}
for p in sorted(q for q in (ROOT / "src").rglob("*.cpp") if "wip" not in q.parts):
    m = LETTER.match(p.stem)
    if not m or SKIP.match(p.stem):
        continue
    base = m["base"]
    new = f"{base}.cpp"
    n = 2
    while taken(new) or any(v.name == new for v in moves.values()):
        new = f"{base}_{n}.cpp"
        n += 1
    moves[p] = p.with_name(new)
hmoves, hmerge = {}, {}
for h in sorted(q for q in (ROOT / "include").rglob("*.h") if "wip" not in q.parts):
    stem = h.stem[:-4] if h.stem.endswith("_api") else h.stem
    m = LETTER.match(stem)
    if not m or SKIP.match(stem):
        continue
    new = h.with_name(m["base"] + ("_api" if h.stem.endswith("_api") else "") + ".h")
    if new.exists() or new in hmoves.values():
        hmerge[h] = new
    else:
        hmoves[h] = new
for a, b in list(moves.items()) + list(hmoves.items()) + list(hmerge.items()):
    print(f"{a.relative_to(ROOT).as_posix()} -> {b.relative_to(ROOT).as_posix()}{' (merge)' if a in hmerge else ''}")
if DRY:
    sys.exit()
for a, b in list(moves.items()) + list(hmoves.items()):
    subprocess.run(["git", "mv", str(a), str(b)], cwd=ROOT, check=True)
for a, b in hmerge.items():
    body = a.read_text(encoding="utf-8")
    body = re.sub(r"^#ifndef \w+\n#define \w+\n", "", body, count=1, flags=re.M)
    body = body[:body.rindex("#endif")].strip("\n")
    t = b.read_text(encoding="utf-8")
    t = t[:t.rindex("#endif")].rstrip("\n") + f"\n\n{body}\n\n#endif\n"
    b.write_text(t, encoding="utf-8", newline="\n")
    subprocess.run(["git", "rm", "-q", str(a)], cwd=ROOT, check=True)
inc = {a.relative_to(ROOT / "include").as_posix(): b.relative_to(ROOT / "include").as_posix()
       for a, b in list(hmoves.items()) + list(hmerge.items())}
pat = re.compile(r'(#include\s+")([^"]+)(")')
for f in list((ROOT / "src").rglob("*.cpp")) + list((ROOT / "include").rglob("*.h")):
    t = f.read_text(encoding="utf-8")
    t2 = pat.sub(lambda m: m.group(1) + inc.get(m.group(2), m.group(2)) + m.group(3), t)
    seen, out = set(), []
    for line in t2.split("\n"):  # a merged header may now be included twice
        if line.startswith("#include") and line in seen:
            continue
        seen.add(line) if line.startswith("#include") else None
        out.append(line)
    t2 = "\n".join(out)
    if t2 != t:
        f.write_text(t2, encoding="utf-8", newline="\n")
src = {a.relative_to(ROOT).as_posix(): b.relative_to(ROOT).as_posix() for a, b in moves.items()}
for cfg in (ROOT / "config/eur/arm9/delinks.txt", ROOT / "scratch/merge_failed.txt"):
    if cfg.exists():
        t = cfg.read_text()
        t = re.sub(r"src/[\w/]+\.cpp", lambda m: src.get(m.group(0), m.group(0)), t)
        cfg.write_text(t, newline="\n")
print(f"renamed {len(moves)} sources, {len(hmoves)} headers, merged {len(hmerge)} headers")
