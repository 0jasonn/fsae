#!/usr/bin/env python3
"""Splits a source file into one file per run of address-contiguous functions, keeping the preamble (includes, types,
declarations before the first function) and any enclosing namespace blocks in every piece.

usage: split_runs.py src/game/file.cpp     (writes file.cpp with the first run and file_N.cpp for the others)
A function block starts at the comment/extern lines directly above its `ARM ` definition line.
"""
import re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
import integrate  # noqa: E402  (method_addr, syms)

DEF = re.compile(r'^ARM (?:extern "C" )?(?:static )?[\w\s\*&:<>]*?\b(~?\w+(?:::~?\w+)*)\s*\([^;\n]*$')
path = Path(sys.argv[1])
lines = path.read_text(encoding="utf-8").rstrip("\n").split("\n")
defs = [i for i, l in enumerate(lines) if DEF.match(l)]
starts = []
for i in defs:
    j = i
    while j > 0 and (lines[j - 1].startswith("//") or lines[j - 1].startswith('extern "C"')):
        j -= 1
    starts.append(j)
opens = [l for l in lines[:starts[0]] if re.match(r"^namespace \w+ \{$", l)]
closes = len(opens)
tail = len(lines)
while closes and tail > 0 and lines[tail - 1].strip() in ("}", ""):
    if lines[tail - 1].strip() == "}":
        closes -= 1
    tail -= 1
pre = lines[:starts[0]]
blocks = [lines[s:e] for s, e in zip(starts, starts[1:] + [tail])]
addrs = [integrate.method_addr(DEF.match(lines[i]).group(1)) for i in defs]
if None in addrs:
    sys.exit(f"cannot resolve {[DEF.match(lines[i]).group(1) for i, a in zip(defs, addrs) if a is None]}")
order = integrate.syms
runs, cur = [], [0]
for k in range(1, len(defs)):
    if order.index(addrs[k]) == order.index(addrs[k - 1]) + 1:
        cur.append(k)
    else:
        runs.append(cur)
        cur = [k]
runs.append(cur)
if len(runs) == 1:
    sys.exit("already contiguous")
close = [""] + ["}"] * len(opens)
stem, n = re.sub(r"_\d+$", "", path.stem), 2
for r_i, run in enumerate(runs):
    body = [l for k in run for l in blocks[k]]
    text = "\n".join(pre + body).rstrip("\n") + ("\n" + "\n".join(close) if opens else "") + "\n"
    if r_i == 0:
        out = path
    else:
        while any(path.parent.parent.glob(f"*/{stem}_{n}.cpp")):
            n += 1
        out = path.with_name(f"{stem}_{n}.cpp")
        n += 1
    out.write_text(text, encoding="utf-8", newline="\n")
    print(f"{out}: {', '.join(hex(addrs[k]) for k in run)}")
