#!/usr/bin/env python3
"""Replaces dsd names (data_XXXXXXXX / func_XXXXXXXX) that no longer exist in symbols.txt with the symbol's current
name, in every integrated source file and header. Run when the link reports them as undefined."""
import re
from pathlib import Path
ROOT = Path(__file__).parent.parent
by_addr, names = {}, set()
for line in (ROOT / "config/eur/arm9/symbols.txt").read_text().splitlines():
    m = re.match(r"(\S+) .*addr:0x([0-9a-f]+)", line)
    if m:
        names.add(m.group(1))
        by_addr.setdefault(int(m.group(2), 16), m.group(1))


def current(name):
    m = re.match(r"_Z(\d+)", name)
    return name[len(m.group(0)):len(m.group(0)) + int(m.group(1))] if m else name


files = [f for f in list((ROOT / "src").rglob("*.cpp")) + list((ROOT / "include").rglob("*.h"))
         if "wip" not in f.parts and f.name != "functions.h"]  # functions.h: stale prototypes are deleted by hand
for f in files:
    s = f.read_text(encoding="utf-8")
    def repl(m):
        if m.group(0) in names:
            return m.group(0)
        new = by_addr.get(int(m.group(2), 16))
        return current(new) if new else m.group(0)
    t = re.sub(r"\b(data|func)_([0-9a-f]{8})\b", repl, s)
    if t != s:
        f.write_text(t, encoding="utf-8", newline="\n")
        print("updated", f.relative_to(ROOT))
