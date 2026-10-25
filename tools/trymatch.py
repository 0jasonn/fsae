#!/usr/bin/env python3
"""Compiles a C/C++ file with one or more mwccarm versions and checks each function against the base ARM9.

Functions must be named func_XXXXXXXX (or have their address in a `// 0xXXXXXXXX` comment-free name) so the
expected address is known. Relocated bits are ignored.
"""

import argparse
import re
import subprocess
import sys
import tempfile
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))
from sdk_sigmatch import extract_functions, matches_at  # noqa: E402

ROOT = Path(__file__).parent.parent
sys.path.insert(0, str(ROOT / "tools"))

DEFAULT_FLAGS = ("-O4,p -enum int -char signed -str noreuse -proc arm946e -gccext,on -fp soft -inline noauto "
                 "-Cpp_exceptions off -RTTI off -interworking -w off -sym on -gccinc -nolink -ipa file")


def diff(target: bytes, code: bytes, mask: bytes, addr: int, thumb: bool) -> str:
    import capstone
    md = capstone.Cs(capstone.CS_ARCH_ARM, capstone.CS_MODE_THUMB if thumb else capstone.CS_MODE_ARM)
    md.skipdata = True

    def dis(buf):
        return {i.address: f"{i.mnemonic} {i.op_str}" for i in md.disasm(buf, addr)}

    a, b = dis(target), dis(code)
    out = []
    for k in sorted(set(a) | set(b)):
        off = k - addr
        same = all(((x ^ y) & m) == 0 for x, y, m in zip(target[off:off + 4], code[off:off + 4], mask[off:off + 4]))
        out.append(f"    {'  ' if same else '>>'} {k:08x}  {a.get(k, ''):40} {b.get(k, '')}")
    return "\n".join(out)


_NAMES = None


def name_to_addr(name):
    """Address of a function: from a func_XXXXXXXX name, symbols.txt, or a pending rename in scratch/agent*/renames.txt."""
    global _NAMES
    if name.startswith("_Z"):  # C++ (Itanium) mangled name: use the plain function name (Class_method for members)
        if _NAMES is not None and name in _NAMES:  # exact mangled symbol first: overloads share a plain name
            return _NAMES[name]
        from cxx_symbols import plain_name
        exact = name
        name = plain_name(name) or name
        if _NAMES is None:
            name_to_addr("_load_names_")  # fills _NAMES
        if exact in _NAMES:
            return _NAMES[exact]
    m = re.fullmatch(r"func_([0-9a-fA-F]{8})(?:_unk)?", name)
    if m:
        return int(m.group(1), 16)
    if _NAMES is None:
        _NAMES = {}
        for line in (ROOT / "config/eur/arm9/symbols.txt").read_text().splitlines():
            sm = re.match(r"(\S+) kind:function\S* addr:0x([0-9a-f]+)", line)
            if sm:
                _NAMES[sm.group(1)] = int(sm.group(2), 16)
                if sm.group(1).startswith("_Z"):  # also index C++ symbols by their plain name
                    from cxx_symbols import plain_name
                    if plain_name(sm.group(1)):
                        _NAMES.setdefault(plain_name(sm.group(1)), int(sm.group(2), 16))
        for ren in (ROOT / "scratch").glob("agent*/renames.txt"):
            for line in ren.read_text().splitlines():
                parts = line.split()
                if len(parts) == 2 and parts[0].startswith("func_"):
                    _NAMES[parts[1]] = int(parts[0][5:13], 16)
    return _NAMES.get(name)


def call_mismatches(obj: bytes, data: bytes, base: int):
    """{function: [(offset, called symbol, original target)]} for ARM bl/blx whose target differs from the ROM.
    The byte comparison masks relocated bits, so a call to the wrong function would otherwise pass."""
    from io import BytesIO
    from elftools.elf.elffile import ELFFile
    from elftools.elf.relocation import RelocationSection
    elf = ELFFile(BytesIO(obj))
    symtab = elf.get_section_by_name(".symtab")
    funcs = [s for s in symtab.iter_symbols() if s["st_info"]["type"] == "STT_FUNC" and isinstance(s["st_shndx"], int)]
    out = {}
    for sec in elf.iter_sections():
        if not isinstance(sec, RelocationSection):
            continue
        for rel in sec.iter_relocations():
            if rel["r_info_type"] not in (1, 28, 29):  # ARM PC24 / CALL / JUMP24
                continue
            target = symtab.get_symbol(rel["r_info_sym"]).name
            want = name_to_addr(target)
            if want is None:
                continue
            for f in funcs:
                start = f["st_value"] & ~1
                if f["st_shndx"] == sec["sh_info"] and start <= rel["r_offset"] < start + f["st_size"] and not f["st_value"] & 1:
                    addr = name_to_addr(f.name)
                    if addr is None:
                        break
                    pc = addr + rel["r_offset"] - start
                    word = int.from_bytes(data[pc - base:pc - base + 4], "little")
                    imm = word & 0xffffff
                    imm = imm - 0x1000000 if imm & 0x800000 else imm
                    got = pc + 8 + imm * 4 + (2 if word >> 28 == 0xf and word & 0x1000000 else 0)
                    if got & ~1 != want & ~1:
                        out.setdefault(f.name, []).append((rel["r_offset"] - start, target, got))
                    break
    return out


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("source", type=Path)
    parser.add_argument("-v", "--versions", nargs="+", default=["dsi/1.2"])
    parser.add_argument("-f", "--flags", default=DEFAULT_FLAGS)
    parser.add_argument("-x", "--extra", default="")
    parser.add_argument("--base-bin", type=Path, default=ROOT / "extract/eur/arm9/arm9.bin")
    parser.add_argument("--base", type=lambda x: int(x, 0), default=0x02004000)
    parser.add_argument("-q", "--quiet", action="store_true")
    parser.add_argument("-d", "--diff", action="store_true", help="Show disassembly of differing functions")
    args = parser.parse_args()

    data = args.base_bin.read_bytes()
    lang = "-lang=c++" if args.source.suffix == ".cpp" else "-lang=c99"
    for version in args.versions:
        cc = ROOT / "tools/mwccarm" / version / "mwccarm.exe"
        with tempfile.TemporaryDirectory() as tmp:
            out = Path(tmp) / "out.o"
            cmd = f'"{cc}" {args.flags} {args.extra} {lang} -i "{ROOT / "include"}" -c "{args.source}" -o "{out}"'
            res = subprocess.run(cmd, shell=True, capture_output=True, text=True)
            if res.returncode != 0 or not out.exists():
                print(f"{version}: compile failed\n{res.stdout}{res.stderr}")
                continue
            ok = bad = 0
            lines = []
            calls = call_mismatches(out.read_bytes(), data, args.base)
            for name, thumb, code, mask in extract_functions(out.read_bytes()):
                addr = name_to_addr(name)
                if addr is None:
                    continue
                good = matches_at(data, addr - args.base, code, mask) and name not in calls
                ok += good
                bad += not good
                lines.append(f"  {'OK  ' if good else 'FAIL'} {name} size={len(code):#x}")
                for off, target, got in calls.get(name, []):
                    lines.append(f"    call at +{off:#x} goes to {target}, the original calls {got:#010x}")
                if args.diff and not good:
                    lines.append(diff(data[addr - args.base:addr - args.base + len(code)], code, mask, addr, thumb))
            print(f"{version}: {ok} match, {bad} differ")
            if not args.quiet:
                print("\n".join(lines))


if __name__ == "__main__":
    main()
