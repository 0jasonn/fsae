#!/usr/bin/env python3
"""Generate the linker script, fixed symbols, and explicit function selections."""

import json
import re
import subprocess
import sys
from pathlib import Path


def select_functions(layout, selections):
    """Keep a unit's mapped functions without placing incidental weak copies."""
    for obj, functions in selections.items():
        if not re.fullmatch(r"[\w.-]+\.o", obj) or not functions:
            raise ValueError(f"Invalid function selection for {obj!r}")
        if len(functions) != len(set(functions)):
            raise ValueError(f"Duplicate function selection for {obj}")
        if any(not re.fullmatch(r"[\w.$@]+", symbol) for symbol in functions):
            raise ValueError(f"Invalid function symbol for {obj}")
        pattern = rf"(?m)^([ \t]*){re.escape(obj)}\(\.text\)[ \t]*$"
        def replace(match):
            return "\n".join(f"{match[1]}OBJECT ({symbol}, {obj})" for symbol in functions)
        layout, count = re.subn(pattern, replace, layout)
        if count != 1:
            raise ValueError(f"Expected one .text selector for {obj}, found {count}")
    return layout


def main():
    dsd, config, lcf_path, symbols_path = sys.argv[1:]
    subprocess.run([dsd, "--force-color", "lcf", "--config-path", config], check=True)

    lcf = Path(lcf_path)
    header, sections, layout = lcf.read_text().partition("SECTIONS {\n")
    if not sections:
        raise SystemExit(f"{lcf}: missing SECTIONS block")
    selections = Path(config).with_name("function_sections.json")
    if selections.exists():
        layout = select_functions(layout, json.loads(selections.read_text()))
    symbols = Path(symbols_path).read_text()
    lcf.write_text(header + sections + symbols + layout, newline="\n")


if __name__ == "__main__":
    main()
