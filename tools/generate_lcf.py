#!/usr/bin/env python3
"""Generate the dsd linker script and add symbols outside the linked ARM9 image."""

import subprocess
import sys
from pathlib import Path


def main():
    dsd, config, lcf_path, symbols_path = sys.argv[1:]
    subprocess.run([dsd, "--force-color", "lcf", "--config-path", config], check=True)

    lcf = Path(lcf_path)
    header, sections, layout = lcf.read_text().partition("SECTIONS {\n")
    if not sections:
        raise SystemExit(f"{lcf}: missing SECTIONS block")
    symbols = Path(symbols_path).read_text()
    lcf.write_text(header + sections + symbols + layout, newline="\n")


if __name__ == "__main__":
    main()
