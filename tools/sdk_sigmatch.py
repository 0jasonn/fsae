#!/usr/bin/env python3
"""Finds functions from prebuilt SDK libraries (.a/.o, ELF) in a binary, ignoring relocated bits.

Prints one JSON object per match: address, name, size, thumb, library and object.
"""

import argparse
import json
import struct
import sys
from io import BytesIO
from pathlib import Path

from elftools.elf.elffile import ELFFile
from elftools.elf.relocation import RelocationSection

R_ARM_PC24 = 1
R_ARM_ABS32 = 2
R_ARM_THM_PC22 = 10
R_ARM_CALL = 28
R_ARM_JUMP24 = 29
R_ARM_THM_JUMP24 = 30


def read_ar(path: Path):
    data = path.read_bytes()
    if not data.startswith(b"!<arch>\n"):
        yield path.name, data
        return
    pos = 8
    names = b""
    while pos + 60 <= len(data):
        header = data[pos:pos + 60]
        name = header[:16].decode("ascii", "replace").strip()
        size = int(header[48:58].decode().strip())
        body = data[pos + 60:pos + 60 + size]
        pos += 60 + size + (size & 1)
        if name == "//":
            names = body
            continue
        if name in ("/", "/SYM64/", "__.SYMDEF"):
            continue
        if name.startswith("/") and name[1:].isdigit():
            off = int(name[1:])
            name = names[off:names.index(b"/", off)].decode()
        name = name.rstrip("/")
        if body.startswith(b"\x7fELF"):
            yield name, body


def mask_for(rtype: int, offset: int, mask: bytearray, thumb: bool):
    if rtype in (R_ARM_PC24, R_ARM_CALL, R_ARM_JUMP24):
        # Keep bits 27..25 (branch class), the linker may turn BL into BLX and change the condition field
        mask[offset:offset + 4] = b"\x00\x00\x00\x0e"
    elif rtype in (R_ARM_THM_PC22, R_ARM_THM_JUMP24):
        mask[offset:offset + 4] = b"\x00\xf8\x00\xe8"
    else:
        mask[offset:offset + 4] = b"\x00\x00\x00\x00"


def extract_functions(obj: bytes):
    elf = ELFFile(BytesIO(obj))
    symtab = elf.get_section_by_name(".symtab")
    if symtab is None:
        return
    relocs: dict[int, list] = {}
    for section in elf.iter_sections():
        if isinstance(section, RelocationSection):
            relocs.setdefault(section["sh_info"], []).extend(section.iter_relocations())

    # Mapping symbols ($a/$t/$d) tell code modes and literal pools apart
    mapping: dict[int, list[tuple[int, str]]] = {}
    for sym in symtab.iter_symbols():
        if sym.name in ("$a", "$t", "$d") and isinstance(sym["st_shndx"], int):
            mapping.setdefault(sym["st_shndx"], []).append((sym["st_value"], sym.name))

    for sym in symtab.iter_symbols():
        if sym["st_info"]["type"] != "STT_FUNC" or not isinstance(sym["st_shndx"], int):
            continue
        size = sym["st_size"]
        if size == 0:
            continue
        shndx = sym["st_shndx"]
        section = elf.get_section(shndx)
        sdata = section.data()
        value = sym["st_value"]
        thumb = bool(value & 1)
        start = value & ~1
        code = bytearray(sdata[start:start + size])
        if len(code) != size:
            continue
        mask = bytearray(b"\xff" * size)
        for rel in relocs.get(shndx, []):
            off = rel["r_offset"] - start
            if 0 <= off < size:
                mask_for(rel["r_info_type"], off, mask, thumb)
        yield sym.name, thumb, bytes(code), bytes(mask)


def longest_unmasked_run(mask: bytes, align: int):
    best = (0, 0)
    run_start = None
    for i in range(0, len(mask) + 1, align):
        full = i < len(mask) and all(b == 0xff for b in mask[i:i + align])
        if full and run_start is None:
            run_start = i
        elif not full and run_start is not None:
            if i - run_start > best[1] - best[0]:
                best = (run_start, i)
            run_start = None
    return best


def matches_at(data: bytes, pos: int, code: bytes, mask: bytes) -> bool:
    if pos < 0 or pos + len(code) > len(data):
        return False
    window = data[pos:pos + len(code)]
    for a, b, m in zip(window, code, mask):
        if (a ^ b) & m:
            return False
    return True


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("binary", type=Path)
    parser.add_argument("--base", type=lambda x: int(x, 0), required=True)
    parser.add_argument("libs", type=Path, nargs="+")
    parser.add_argument("--min-size", type=int, default=12)
    args = parser.parse_args()

    data = args.binary.read_bytes()
    seen = set()
    for lib in args.libs:
        for obj_name, obj in read_ar(lib):
            for name, thumb, code, mask in extract_functions(obj):
                if len(code) < args.min_size:
                    continue
                key = (name, code, mask)
                if key in seen:
                    continue
                seen.add(key)
                align = 2 if thumb else 4
                run_start, run_end = longest_unmasked_run(mask, align)
                if run_end - run_start < 8:
                    continue
                needle = code[run_start:run_end]
                hits = []
                pos = data.find(needle)
                while pos != -1 and len(hits) < 3:
                    func_pos = pos - run_start
                    if func_pos % align == 0 and matches_at(data, func_pos, code, mask):
                        hits.append(func_pos)
                    pos = data.find(needle, pos + 1)
                if len(hits) == 1:
                    print(json.dumps({
                        "address": args.base + hits[0], "name": name, "size": len(code), "thumb": thumb,
                        "lib": lib.name, "object": obj_name,
                    }))
                elif len(hits) > 1:
                    print(f"ambiguous: {name} ({lib.name}:{obj_name}) {len(hits)}+ hits", file=sys.stderr)


if __name__ == "__main__":
    main()
