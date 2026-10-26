#!/usr/bin/env python3
"""Splits a source file into one file per run of address-contiguous functions. Every piece keeps all the lines that
are not inside a function (includes, types, declarations, namespace lines, also ones between functions), so each
piece compiles on its own.

usage: split_runs.py src/game/file.cpp     (writes file.cpp with the first run and file_N.cpp for the others)
A function block is its `ARM ` definition line through the brace that closes it, plus the comment and extern "C"
lines directly above it.
"""
import re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
import integrate  # noqa: E402  (method_addr, syms)

DEF = re.compile(r'^ARM (?:extern "C" )?(?:static )?[\w\s\*&:<>]*?\b(~?\w+(?:::~?\w+)*)\s*\([^;\n]*$')
path = Path(sys.argv[1])
lines = path.read_text(encoding="utf-8").rstrip("\n").split("\n")
owner = [None] * len(lines)  # index of the function block a line belongs to
names = []
for i, l in enumerate(lines):
    m = DEF.match(l)
    if not m:
        continue
    k = len(names)
    names.append(m.group(1))
    j = i
    while j > 0 and owner[j - 1] is None and (lines[j - 1].startswith("//") or lines[j - 1].startswith('extern "C"')):
        j -= 1
    depth, e, seen = 0, i, False
    while e < len(lines):
        depth += lines[e].count("{") - lines[e].count("}")
        seen = seen or "{" in lines[e]
        if seen and depth <= 0:
            break
        e += 1
    for x in range(j, e + 1):
        owner[x] = k
addrs = [integrate.method_addr(n) for n in names]
if None in addrs:
    sys.exit(f"cannot resolve {[n for n, a in zip(names, addrs) if a is None]}")
order = integrate.syms
runs, cur = [], [0]
for k in range(1, len(names)):
    if order.index(addrs[k]) == order.index(addrs[k - 1]) + 1:
        cur.append(k)
    else:
        runs.append(cur)
        cur = [k]
runs.append(cur)
if len(runs) == 1:
    sys.exit("already contiguous")
stem, n = re.sub(r"_\d+$", "", path.stem), 2
for r_i, run in enumerate(runs):
    keep = set(run)
    text = "\n".join(l for l, o in zip(lines, owner) if o is None or o in keep) + "\n"
    text = re.sub(r"\n{3,}", "\n\n", text)
    if r_i == 0:
        out = path
    else:
        while any(path.parent.parent.glob(f"*/{stem}_{n}.cpp")):
            n += 1
        out = path.with_name(f"{stem}_{n}.cpp")
        n += 1
    out.write_text(text, encoding="utf-8", newline="\n")
    print(f"{out}: {', '.join(hex(addrs[k]) for k in run)}")
