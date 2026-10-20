#!/usr/bin/env python3
"""Splits a source file into one file per run of address-contiguous functions (each keeps the shared preamble).
New files are named <module>_<n>.cpp with the next free number. Usage: python tools/split_unit.py src/game/backup.cpp"""
import re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
from trymatch import name_to_addr

ROOT = Path(__file__).parent.parent
DEF = re.compile(r'^ARM (?:extern "C" )?(?:static )?[\w\s\*]*?\b(\w+)\s*\([^;\n]*$')
syms = sorted(int(m.group(1), 16) for m in re.finditer(r"kind:function\S* addr:0x([0-9a-f]+)",
                                                         (ROOT / "config/eur/arm9/symbols.txt").read_text()))
path = Path(sys.argv[1])
lines = path.read_text(encoding="utf-8").split("\n")
starts = [i for i, l in enumerate(lines) if DEF.match(l)]
begins = []
for i in starts:
    j = i
    while j > 0 and lines[j - 1].startswith("//") and j - 1 not in starts:
        j -= 1
    begins.append(j)
pre = "\n".join(lines[:begins[0]])
blocks = []
for b, e, i in zip(begins, begins[1:] + [len(lines)], starts):
    blocks.append((name_to_addr(DEF.match(lines[i]).group(1)), "\n".join(lines[b:e]).rstrip("\n") + "\n"))
blocks.sort()
groups = []
for a, t in blocks:
    if groups and syms.index(a) == syms.index(groups[-1][-1][0]) + 1:
        groups[-1].append((a, t))
    else:
        groups.append([(a, t)])
module = re.sub(r"_\d+$", "", path.stem)
n = 2
for k, g in enumerate(groups):
    if k == 0:
        out = path
    else:
        while (path.parent / f"{module}_{n}.cpp").exists():
            n += 1
        out = path.parent / f"{module}_{n}.cpp"
    out.write_text(pre + "\n" + "\n".join(t for _, t in g), encoding="utf-8", newline="\n")
    print(out, len(g), hex(g[0][0]))
