#!/usr/bin/env python3
"""Prints dsd's disassembly for one function, or every function in an address range."""

import argparse
import re
from pathlib import Path

ROOT = Path(__file__).parent.parent


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("start", type=lambda x: int(x, 16))
    parser.add_argument("end", type=lambda x: int(x, 16), nargs="?")
    parser.add_argument("--asm-dir", type=Path, default=ROOT / "build/eur/asm")
    args = parser.parse_args()
    end = args.end if args.end is not None else args.start + 1

    printing = False
    lines = []
    for path in sorted(args.asm_dir.rglob("*.s")):
        lines.extend(path.read_text().splitlines())
    for line in lines:
        m = re.match(r"^(\S+): ; 0x([0-9a-f]{8})$", line)
        if m:
            addr = int(m.group(2), 16)
            printing = args.start <= addr < end
        if printing and line.strip() and not line.lstrip().startswith((".global", "arm_func_start", "thumb_func_start")):
            print(line)
        if line.lstrip().startswith(("arm_func_end", "thumb_func_end")):
            printing = False


if __name__ == "__main__":
    main()
