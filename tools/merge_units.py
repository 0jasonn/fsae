#!/usr/bin/env python3
"""Merges the split files of one module back together once nothing separates them.

dsd needs every unit to cover one unbroken address range, so a module whose functions are interrupted by a
not-yet-decompiled function is split into module.cpp, module_2.cpp, ... When the gap is filled, the neighbouring units
of the same module (same directory, same name without the _N suffix) touch, and this tool joins them: the code of the
later files is appended to the first one (includes, declarations and struct definitions it already has are dropped),
the delinks units become one, and the merged file is checked with trymatch. A chain whose merge does not compile or
match is left as it was. Only units with nothing but a .text section are merged.
usage: merge_units.py [--dry]
"""
import re, subprocess, sys
from pathlib import Path

ROOT = Path(__file__).parent.parent
DELINKS = ROOT / "config/eur/arm9/delinks.txt"
DRY = "--dry" in sys.argv
UNIT = re.compile(r"^(src/\S+\.cpp):\n((?:    .*\n)+)\n?", re.M)
STRUCT = re.compile(r"^typedef struct (\w+) \{.*?^\} \1;[^\n]*\n", re.S | re.M)


def module(path):
    return re.sub(r"_\d+$", "", path[:-4])


def units():
    out = []
    for m in UNIT.finditer(DELINKS.read_text()):
        secs = re.findall(r"^\s+(\.\w+)\s+start:0x([0-9a-f]+) end:0x([0-9a-f]+)", m.group(2), re.M)
        if len(secs) == 1 and secs[0][0] == ".text":
            out.append((int(secs[0][1], 16), int(secs[0][2], 16), m.group(1)))
    return sorted(out)


def chains():
    us, out, cur = units(), [], []
    for u in us:
        if cur and cur[-1][1] == u[0] and module(cur[-1][2]) == module(u[2]):
            cur.append(u)
        else:
            if len(cur) > 1:
                out.append(cur)
            cur = [u]
    if len(cur) > 1:
        out.append(cur)
    return out


def merged_text(paths):
    base = (ROOT / paths[0]).read_text(encoding="utf-8").rstrip("\n")
    have_lines = set(base.split("\n"))
    have_structs = set(STRUCT.findall(base))
    for p in paths[1:]:
        text = (ROOT / p).read_text(encoding="utf-8")
        text = STRUCT.sub(lambda m: "" if m.group(1) in have_structs else m.group(0), text)
        have_structs |= set(STRUCT.findall(text))
        keep = []
        for line in text.split("\n"):
            decl = line.startswith(("#include", "extern ", "typedef ", "struct ", "#define ")) or \
                re.match(r"^[\w\s\*]+\w+\([^)]*\);\s*(//.*)?$", line)
            if decl and line in have_lines:
                continue
            keep.append(line)
            have_lines.add(line)
        body = "\n".join(keep)
        incs = [l for l in body.split("\n") if l.startswith("#include")]
        body = "\n".join(l for l in body.split("\n") if not l.startswith("#include"))
        if incs:  # a new include goes to the top with the others
            lines = base.split("\n")
            last = max(i for i, l in enumerate(lines) if l.startswith("#include"))
            lines[last + 1:last + 1] = incs
            base = "\n".join(lines)
        base += "\n\n" + body.strip("\n")
    return re.sub(r"\n{3,}", "\n\n", base) + "\n"


def matches(path, count):
    r = subprocess.run([sys.executable, str(ROOT / "tools/trymatch.py"), str(path), "-q"], capture_output=True, text=True)
    return f"{count} match, 0 differ" in r.stdout


def func_count(paths):
    n = 0
    for p in paths:
        r = subprocess.run([sys.executable, str(ROOT / "tools/trymatch.py"), str(ROOT / p), "-q"], capture_output=True, text=True)
        m = re.search(r"(\d+) match, 0 differ", r.stdout)
        if not m:
            return None
        n += int(m.group(1))
    return n


done = 0
for chain in chains():
    paths = [u[2] for u in chain]
    # the merged file takes the plain module name when that name is one of the pieces, else the first piece's name
    target = module(paths[0]) + ".cpp"
    target = target if target in paths else paths[0]
    if DRY:
        print(f"{' + '.join(paths)} -> {target}")
        done += 1
        continue
    count = func_count(paths)
    if count is None:
        print(f"skip {paths[0]}: a piece does not match on its own")
        continue
    saved = {p: (ROOT / p).read_text(encoding="utf-8") for p in paths}
    text = merged_text(paths)
    for p in paths:
        (ROOT / p).unlink()
    (ROOT / target).write_text(text, encoding="utf-8", newline="\n")
    if not matches(ROOT / target, count):
        (ROOT / target).unlink()
        for p, t in saved.items():
            (ROOT / p).write_text(t, encoding="utf-8", newline="\n")
        print(f"undone {target}: merged file does not compile or match")
        continue
    d = DELINKS.read_text()
    first = True
    for p in paths:
        m = re.search(rf"^{re.escape(p)}:\n(?:    .*\n)+\n?", d, re.M)
        if first:
            d = d.replace(m.group(0), f"{target}:\n    complete\n    .text       start:{chain[0][0]:#010x} "
                                      f"end:{chain[-1][1]:#010x}\n\n", 1)
            first = False
        else:
            d = d.replace(m.group(0), "", 1)
    DELINKS.write_text(d, newline="\n")
    done += 1
    print(f"{' + '.join(paths)} -> {target}")
print(f"{done} chains merged")
