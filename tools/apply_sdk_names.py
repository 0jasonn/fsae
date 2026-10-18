#!/usr/bin/env python3
"""Renames symbols in symbols.txt using matches from sdk_sigmatch.py (one JSON object per line)."""

import argparse
import collections
import json
import re
from pathlib import Path

ROOT = Path(__file__).parent.parent


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("matches", type=Path, nargs="?", default=ROOT / "config/eur/sdk_matches.jsonl")
    parser.add_argument("--symbols", type=Path, default=ROOT / "config/eur/arm9/symbols.txt")
    args = parser.parse_args()

    matches = [json.loads(l) for l in args.matches.read_text().splitlines() if l.strip()]
    counts = collections.Counter(m["name"] for m in matches)
    by_addr = {}
    for m in matches:
        name = m["name"] if counts[m["name"]] == 1 else f"{m['name']}_{m['address']:08x}"
        by_addr[m["address"]] = (name, m)

    lines = args.symbols.read_text().splitlines()
    renamed = 0
    for i, line in enumerate(lines):
        sym = re.match(r"(\S+) kind:(function|label)\((arm|thumb)[^)]*\) addr:0x([0-9a-f]+)", line)
        if not sym:
            continue
        addr = int(sym.group(4), 16)
        if addr not in by_addr or (sym.group(3) == "thumb") != by_addr[addr][1]["thumb"]:
            continue
        old, new = sym.group(1), by_addr[addr][0]
        # Only rename generated names, dsd relies on some of its own (e.g. Entry)
        if not old.startswith(("func_", ".L_")):
            continue
        if old != new:
            lines[i] = new + line[len(old):]
            renamed += 1
    args.symbols.write_text("\n".join(lines) + "\n", newline="\n")
    print(f"Renamed {renamed} symbols")


if __name__ == "__main__":
    main()
