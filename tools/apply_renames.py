#!/usr/bin/env python3
"""Applies a renames file (lines: old new) to symbols.txt and every reference in src/ and include/."""
import re, sys
from pathlib import Path
ROOT = Path(__file__).parent.parent
pairs = [l.split() for l in Path(sys.argv[1]).read_text().splitlines() if len(l.split()) == 2]
symp = ROOT / "config/eur/arm9/symbols.txt"
syms = symp.read_text()
existing = {l.split(" ", 1)[0] for l in syms.splitlines()}
def plain(name):
    m = re.match(r"_Z(\d+)", name)
    return name[len(m.group(0)):len(m.group(0)) + int(m.group(1))] if m else name
plains = {plain(n) for n in existing}
for old, new in pairs:
    if new in plains:
        sys.exit(f"{new} is already used")
    if old in existing:
        syms = re.sub(rf"^{re.escape(old)} ", f"{new} ", syms, flags=re.M)
    else:
        # C++ symbol: replace the plain name inside the mangled one, e.g. _Z12func_0204a110v -> _Z9Telop_Endv
        mangled = [n for n in existing if n.startswith("_Z") and plain(n) == old]
        if len(mangled) != 1:
            sys.exit(f"{old} is not a symbol")
        m = mangled[0]
        head = re.match(r"_Z\d+", m).group(0)
        renamed = f"_Z{len(new)}{new}{m[len(head) + len(old):]}"
        syms = re.sub(rf"^{re.escape(m)} ", f"{renamed} ", syms, flags=re.M)
        existing.discard(m); existing.add(renamed)
    plains.discard(old); plains.add(new)
symp.write_text(syms, newline="\n")
for f in list((ROOT / "src").rglob("*.c")) + list((ROOT / "src").rglob("*.cpp")) + list((ROOT / "include").rglob("*.h")):
    s = f.read_text(); t = s
    for old, new in pairs:
        t = re.sub(rf"\b{re.escape(old)}\b", new, t)
    if t != s:
        f.write_text(t)
        print("updated", f.relative_to(ROOT))
print(f"applied {len(pairs)} renames")
