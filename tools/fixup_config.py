#!/usr/bin/env python3
"""Fixes known problems in a fresh `dsd init` output for this game. Run it after every `dsd init`.

- Removes the bogus Thumb function dsd finds at 0x0208bcd2 (the bytes are an ARM function at 0x0208bcd4) and the
  branch relocation it creates.
- Gives labels that are targets of function calls a `func_` name, so C code can call them.
- Makes labels non-local when another function refers to them (found by running `dsd delink`).
"""

import argparse
import re
import subprocess
from pathlib import Path

ROOT = Path(__file__).parent.parent


def fix_bogus_function(symbols: list[str], relocs: list[str]):
    symbols[:] = [
        l for l in symbols
        if not l.startswith("func_0208bcd2 ") and not l.startswith("func_0208b819_unk ")
    ]
    symbols[:] = [
        re.sub(r"^\.L_0208bcd4 kind:label\(arm\) addr:0x0208bcd4.*$",
               "func_0208bcd4 kind:function(arm,size=0x8) addr:0x0208bcd4", l)
        for l in symbols
    ]
    if not any(l.startswith("func_0208bcd4 ") for l in symbols):
        symbols.append("func_0208bcd4 kind:function(arm,size=0x8) addr:0x0208bcd4")
    relocs[:] = [l for l in relocs if not l.startswith("from:0x0208bcd6 ")]


def name_call_targets(symbols: list[str], relocs: list[str]) -> int:
    targets = set()
    for l in relocs:
        m = re.match(r"from:0x[0-9a-f]+ kind:(?:arm_call|arm_call_thumb|thumb_call|thumb_call_arm) to:0x([0-9a-f]+)", l)
        if m:
            targets.add(int(m.group(1), 16))
    count = 0
    for i, l in enumerate(symbols):
        m = re.match(r"\.L_([0-9a-f]{8}) (kind:label\((?:arm|thumb)\)) addr:0x([0-9a-f]+)(.*)", l)
        if m and int(m.group(3), 16) in targets:
            symbols[i] = f"func_{m.group(1)} {m.group(2)} addr:0x{m.group(3)}{m.group(4)}"
            count += 1
    return count


def unmark_local_labels(symbols_path: Path, config_path: Path) -> int:
    fixed = 0
    for _ in range(10):
        res = subprocess.run([str(ROOT / "tools/dsd.exe"), "delink", "--config-path", str(config_path)],
                             capture_output=True, text=True)
        names = set(re.findall(r"Imported symbol (\S+) at 0x[0-9a-f]+ in .* is local", res.stdout + res.stderr))
        if not names:
            return fixed
        lines = symbols_path.read_text().splitlines()
        for i, l in enumerate(lines):
            name = l.split(" ", 1)[0]
            if name in names and l.endswith(" local"):
                lines[i] = l[:-len(" local")]
                fixed += 1
        symbols_path.write_text("\n".join(lines) + "\n", newline="\n")
    return fixed


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("config_dir", type=Path, nargs="?", default=ROOT / "config/eur/arm9")
    args = parser.parse_args()

    symbols_path = args.config_dir / "symbols.txt"
    relocs_path = args.config_dir / "relocs.txt"
    symbols = symbols_path.read_text().splitlines()
    relocs = relocs_path.read_text().splitlines()

    fix_bogus_function(symbols, relocs)
    renamed = name_call_targets(symbols, relocs)
    symbols_path.write_text("\n".join(symbols) + "\n", newline="\n")
    relocs_path.write_text("\n".join(relocs) + "\n", newline="\n")
    print(f"Named {renamed} call target labels")

    fixed = unmark_local_labels(symbols_path, args.config_dir / "config.yaml")
    print(f"Made {fixed} labels non-local")


if __name__ == "__main__":
    main()
