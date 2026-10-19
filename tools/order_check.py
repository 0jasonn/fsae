#!/usr/bin/env python3
"""Checks that functions in each source file are defined in address order (the linker keeps file order).
With --fix, reorders the function blocks (each block runs from its definition line to the next one)."""
import re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
from trymatch import name_to_addr

DEF = re.compile(r'^ARM (?:static )?[\w\s\*]*?\b(\w+)\s*\([^;\n]*$', re.M)
fix = "--fix" in sys.argv
bad = 0
for path in [Path(a) for a in sys.argv[1:] if a != "--fix"]:
    lines = path.read_text(encoding="utf-8").split("\n")
    starts = [i for i, l in enumerate(lines) if DEF.match(l)]
    addrs = [name_to_addr(DEF.match(lines[i]).group(1)) for i in starts]
    if addrs == sorted(addrs, key=lambda a: a or 0):
        continue
    bad += 1
    print(f"{path}: functions out of address order")
    if fix:
        # a block also takes the comment lines directly above its definition
        begins = []
        for i in starts:
            j = i
            while j > 0 and lines[j - 1].startswith("//"):
                j -= 1
            begins.append(j)
        ends = begins[1:] + [len(lines)]
        blocks = [("\n".join(lines[b:e]).rstrip("\n") + "\n", a) for b, e, a in zip(begins, ends, addrs)]
        head = "\n".join(lines[:begins[0]])
        body = "\n".join(t for t, _ in sorted(blocks, key=lambda x: x[1] or 0))
        path.write_text(head + "\n" + body, encoding="utf-8", newline="\n")
        print("  reordered")
sys.exit(1 if bad and not fix else 0)
