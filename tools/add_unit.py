#!/usr/bin/env python3
"""Adds a complete .text unit to delinks.txt, from its first function to the function after its last one.

Usage: add_unit.py src/path/file.cpp FIRST_ADDR LAST_ADDR
"""

import argparse
import re
from pathlib import Path

ROOT = Path(__file__).parent.parent


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("path")
    parser.add_argument("first", type=lambda x: int(x, 16))
    parser.add_argument("last", type=lambda x: int(x, 16))
    parser.add_argument("--config", type=Path, default=ROOT / "config/eur/arm9")
    args = parser.parse_args()

    funcs = []
    for line in (args.config / "symbols.txt").read_text().splitlines():
        m = re.match(r"\S+ kind:function\((?:arm|thumb),size=0x([0-9a-f]+)[^)]*\) addr:0x([0-9a-f]+)", line)
        if m:
            funcs.append((int(m.group(2), 16), int(m.group(1), 16)))
    funcs.sort()
    addrs = [a for a, _ in funcs]
    if args.first not in addrs or args.last not in addrs:
        raise SystemExit("first/last must be function addresses")
    after = [a for a in addrs if a > args.last]
    end = after[0] if after else args.last + dict(funcs)[args.last]

    delinks = args.config / "delinks.txt"
    text = delinks.read_text().rstrip("\n")
    if f"\n{args.path}:" in text:
        raise SystemExit(f"{args.path} is already in delinks.txt")
    text += f"\n\n{args.path}:\n    complete\n    .text       start:{args.first:#010x} end:{end:#010x}\n"
    delinks.write_text(text, newline="\n")
    print(f"{args.path}: {args.first:#010x}..{end:#010x}")


if __name__ == "__main__":
    main()
