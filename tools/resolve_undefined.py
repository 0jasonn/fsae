#!/usr/bin/env python3
"""Finds the ROM address behind data names a source uses but symbols.txt does not have, and renames them.

For every R_ARM_ABS32 relocation (a literal pool word) in the given objects whose symbol is not in symbols.txt, the
original word at the same place in the ROM is the symbol's address. The matching data_XXXXXXXX entry in symbols.txt is
renamed to the source's name. Usage: python tools/resolve_undefined.py build/eur/src/object/set46.o [...]
"""
import re, subprocess, sys
from io import BytesIO
from pathlib import Path
from elftools.elf.elffile import ELFFile
from elftools.elf.relocation import RelocationSection

sys.path.insert(0, str(Path(__file__).parent))
from trymatch import name_to_addr

ROOT = Path(__file__).parent.parent
BASE = 0x02004000
rom = (ROOT / "extract/eur/arm9/arm9.bin").read_bytes()
lines = (ROOT / "config/eur/arm9/symbols.txt").read_text().splitlines()
names = {l.split(" ", 1)[0] for l in lines}
by_addr = {}
for l in lines:
    m = re.match(r"(\S+) kind:(data|bss)\S* addr:0x([0-9a-f]+)", l)
    if m:
        by_addr.setdefault(int(m.group(3), 16), m.group(1))

renames = {}
for path in sys.argv[1:]:
    elf = ELFFile(BytesIO(Path(path).read_bytes()))
    symtab = elf.get_section_by_name(".symtab")
    funcs = [s for s in symtab.iter_symbols() if s["st_info"]["type"] == "STT_FUNC" and isinstance(s["st_shndx"], int)]
    for sec in elf.iter_sections():
        if not isinstance(sec, RelocationSection):
            continue
        for rel in sec.iter_relocations():
            if rel["r_info_type"] != 2:  # R_ARM_ABS32
                continue
            sym = symtab.get_symbol(rel["r_info_sym"])
            if sym.name in names or sym["st_shndx"] != "SHN_UNDEF":
                continue
            for f in funcs:
                start = f["st_value"] & ~1
                if f["st_shndx"] == sec["sh_info"] and start <= rel["r_offset"] < start + f["st_size"] + 0x400:
                    addr = name_to_addr(f.name)
                    if addr is None:
                        continue
                    pc = addr + rel["r_offset"] - start
                    target = int.from_bytes(rom[pc - BASE:pc - BASE + 4], "little") - rel.entry.get("r_addend", 0)
                    old = by_addr.get(target)
                    if old and old.startswith("data_"):
                        renames.setdefault(sym.name, old)
                    break
out = ROOT / "scratch/resolved_renames.txt"
out.write_text("".join(f"{old} {new}\n" for new, old in renames.items()), newline="\n")
print(f"{len(renames)} names resolved -> {out}")
for new, old in renames.items():
    print(f"  {old} -> {new}")
