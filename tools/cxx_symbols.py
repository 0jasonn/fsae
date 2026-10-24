#!/usr/bin/env python3
"""Updates symbols.txt with the C++ (mangled) names the compiled objects use.

The C++ sources produce Itanium-mangled symbols (`_Z9em09_initP9OBJ_WORK_`), while symbols.txt holds plain names.
For every mangled symbol defined or referenced by an object in build/eur/src, the symbols.txt entry with the same
plain name is renamed to the mangled one. A plain name used with two different signatures is reported, because
only one of them can link. Run after `ninja` has compiled the objects (the link step may fail before this).

Usage: python tools/cxx_symbols.py [--dry-run]
"""
import argparse, collections, re, struct, sys
from pathlib import Path

ROOT = Path(__file__).parent.parent
SYMBOLS = ROOT / "config/eur/arm9/symbols.txt"


def elf_symbols(path):
    """(name, defined) for every global/weak symbol of an ELF32 little-endian object."""
    d = path.read_bytes()
    shoff, = struct.unpack_from("<I", d, 0x20)
    shentsize, shnum = struct.unpack_from("<HH", d, 0x2e)
    secs = [struct.unpack_from("<10I", d, shoff + i * shentsize) for i in range(shnum)]
    out = []
    for s in secs:
        if s[1] != 2:  # SHT_SYMTAB
            continue
        strtab = secs[s[6]]
        for off in range(s[4], s[4] + s[5], 16):
            name_off, value, size, info, other, shndx = struct.unpack_from("<IIIBBH", d, off)
            if info >> 4 == 0:  # local
                continue
            end = d.index(b"\0", strtab[4] + name_off)
            name = d[strtab[4] + name_off:end].decode()
            if name:
                out.append((name, shndx != 0))
    return out


def plain_name(mangled):
    """Plain symbols.txt name of an Itanium-mangled name: `_Z9em09_initP9OBJ_WORK_` -> `em09_init`; nested
    (class or namespace) names join their parts with `_`: `_ZNK5Knife3Hud10HudManager9getStateEv` -> `Knife_Hud_HudManager_getState`."""
    m = re.match(r"_ZN(?:K|V|r)*", mangled)
    if m:
        i, parts = len(m.group(0)), []
        while i < len(mangled) and mangled[i].isdigit():
            n = re.match(r"\d+", mangled[i:]).group(0)
            i += len(n)
            parts.append(mangled[i:i + int(n)])
            i += int(n)
        if parts and i < len(mangled) and mangled[i] == "E":
            return "_".join(parts)
        # Constructors and destructors, named like the debug build: Class_Class (ctor), Class_dtor_Class (deleting
        # dtor), Class_dtorComplete_Class (complete dtor). Base-object variants (C2, D2) alias the complete ones.
        special = {"C1": "_", "D0": "_dtor_", "D1": "_dtorComplete_"}.get(mangled[i:i + 2])
        if parts and special and mangled[i + 2:i + 3] == "E":
            return "_".join(parts) + special + parts[-1]
        return None
    m = re.match(r"_Z(\d+)", mangled)
    if not m:
        return None
    start = len(m.group(0))
    return mangled[start:start + int(m.group(1))]


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--dry-run", action="store_true")
    args = ap.parse_args()

    uses = collections.defaultdict(lambda: collections.defaultdict(set))  # plain -> mangled -> objects
    plain_refs = collections.defaultdict(set)
    for obj in sorted((ROOT / "build/eur/src").rglob("*.o")):
        for name, defined in elf_symbols(obj):
            base = plain_name(name)
            if base:
                uses[base][name].add(obj.relative_to(ROOT / "build/eur").as_posix())
            else:
                plain_refs[name].add(obj.relative_to(ROOT / "build/eur").as_posix())

    lines = SYMBOLS.read_text().splitlines()
    index = {l.split(" ", 1)[0]: i for i, l in enumerate(lines)}
    renamed = conflicts = missing = 0
    for base, variants in sorted(uses.items()):
        if len(variants) > 1:
            conflicts += 1
            print(f"CONFLICT {base}: " + "; ".join(f"{m} in {', '.join(sorted(o))}" for m, o in variants.items()))
            continue
        mangled = next(iter(variants))
        if mangled in index:
            continue
        if base not in index:
            missing += 1
            print(f"MISSING {base} ({mangled}) used by {', '.join(sorted(variants[mangled]))}")
            continue
        i = index.pop(base)
        lines[i] = mangled + lines[i][len(base):]
        index[mangled] = i
        renamed += 1
    for name, objs in sorted(plain_refs.items()):
        if name not in index and not name.startswith(("@", ".", "$")):
            missing += 1
            print(f"MISSING plain {name} used by {', '.join(sorted(objs))}")
    print(f"renamed {renamed}, conflicts {conflicts}, missing {missing}", file=sys.stderr)
    if not args.dry_run:
        SYMBOLS.write_text("\n".join(lines) + "\n", newline="\n")


if __name__ == "__main__":
    main()
