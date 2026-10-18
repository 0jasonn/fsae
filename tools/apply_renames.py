#!/usr/bin/env python3
"""Applies a renames file (lines: old new) to symbols.txt and every reference in src/ and include/."""
import re, sys
from pathlib import Path
ROOT = Path(__file__).parent.parent
pairs = [l.split() for l in Path(sys.argv[1]).read_text().splitlines() if len(l.split()) == 2]
symp = ROOT / "config/eur/arm9/symbols.txt"
syms = symp.read_text()
existing = {l.split(" ", 1)[0] for l in syms.splitlines()}
for old, new in pairs:
    if old not in existing:
        sys.exit(f"{old} is not a symbol")
    if new in existing:
        sys.exit(f"{new} is already used")
    syms = re.sub(rf"^{re.escape(old)} ", f"{new} ", syms, flags=re.M)
    existing.discard(old); existing.add(new)
symp.write_text(syms, newline="\n")
for f in list((ROOT / "src").rglob("*.c")) + list((ROOT / "include").rglob("*.h")):
    s = f.read_text(); t = s
    for old, new in pairs:
        t = re.sub(rf"\b{re.escape(old)}\b", new, t)
    if t != s:
        f.write_text(t)
        print("updated", f.relative_to(ROOT))
print(f"applied {len(pairs)} renames")
