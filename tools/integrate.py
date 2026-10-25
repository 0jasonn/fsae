#!/usr/bin/env python3
"""Verifies implementer files (all functions match, contiguous) and adds them as delinks units."""
import re, subprocess, sys
sys.path.insert(0, str(__import__("pathlib").Path(__file__).parent))
from trymatch import name_to_addr
from pathlib import Path
ROOT = Path(__file__).parent.parent
syms = []
for l in (ROOT / "config/eur/arm9/symbols.txt").read_text().splitlines():
    m = re.match(r"\S+ kind:function\((?:arm|thumb),size=0x([0-9a-f]+)[^)]*\) addr:0x([0-9a-f]+)", l)
    if m: syms.append(int(m.group(2), 16))
syms.sort()


def method_addr(name):
    """Address of a definition name; `Class::method` (inside namespaces) maps to the symbol ending in Class_method."""
    flat = name.replace("::", "_")
    a = name_to_addr(flat)
    if a is None:
        import trymatch
        hits = {v for k, v in trymatch._NAMES.items() if k.endswith("_" + flat)}
        a = hits.pop() if len(hits) == 1 else None
    return a


if __name__ == "__main__":
    for path in sys.argv[1:]:
        src = Path(path).read_text()
        names = re.findall(r'^ARM (?:extern "C" )?(?:static )?[\w\s\*&:<>]*?\b(\w+(?:::\w+)*)\s*\([^;\n]*$', src, re.M)
        addrs = sorted(a for a in (method_addr(n) for n in names) if a is not None)
        r = subprocess.run([sys.executable, str(ROOT / "tools/trymatch.py"), path, "-q"], capture_output=True, text=True).stdout.strip()
        idx = [syms.index(a) for a in addrs]
        contiguous = idx == list(range(idx[0], idx[0] + len(idx)))
        ok = f"{len(addrs)} match, 0 differ" in r and subprocess.run([sys.executable, str(ROOT / "tools/order_check.py"), path]).returncode == 0
        print(f"{path}: {len(addrs)} funcs {addrs[0]:#x}..{addrs[-1]:#x} match={ok} contiguous={contiguous}")
        if ok and contiguous:
            rel = Path(path).as_posix()
            subprocess.run([sys.executable, str(ROOT / "tools/add_unit.py"), rel, f"{addrs[0]:08x}", f"{addrs[-1]:08x}"])
