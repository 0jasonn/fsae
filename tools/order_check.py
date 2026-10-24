#!/usr/bin/env python3
"""Checks that functions in each source file are defined in address order (the linker keeps file order).
With --fix, reorders the function blocks (each block runs from its definition line to the next one)."""
import re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
from trymatch import name_to_addr

DEF = re.compile(r'^ARM (?:extern "C" )?(?:static )?[\w\s\*&:<>]*?\b(~?\w+(?:::~?\w+)*)\s*\([^;\n]*$', re.M)


def def_addr(name):
    """Address of a definition name; `Class::method` maps to the symbol ending in Class_method, `~Class` to a dtor."""
    flat = name.replace("::~", "_dtor_").replace("::", "_")
    a = name_to_addr(flat)
    if a is None:
        import trymatch
        hits = {v for k, v in (trymatch._NAMES or {}).items() if k.endswith("_" + flat)}
        a = hits.pop() if len(hits) == 1 else None
    return a
fix = "--fix" in sys.argv
bad = 0
for path in [Path(a) for a in sys.argv[1:] if a != "--fix"]:
    lines = path.read_text(encoding="utf-8").split("\n")
    starts = [i for i, l in enumerate(lines) if DEF.match(l)]
    addrs = [def_addr(DEF.match(lines[i]).group(1)) for i in starts]
    known = [a for a in addrs if a is not None]  # names that cannot be resolved are not checked
    if known == sorted(known):
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
