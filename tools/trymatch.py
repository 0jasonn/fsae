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
            for name, thumb, code, mask in extract_functions(out.read_bytes()):
                m = re.search(r"([0-9a-fA-F]{8})", name)
                if not m:
                    continue
                addr = int(m.group(1), 16)
                good = matches_at(data, addr - args.base, code, mask)
                ok += good
                bad += not good
                lines.append(f"  {'OK  ' if good else 'FAIL'} {name} size={len(code):#x}")
                if args.diff and not good:
                    lines.append(diff(data[addr - args.base:addr - args.base + len(code)], code, mask, addr, thumb))
            print(f"{version}: {ok} match, {bad} differ")
            if not args.quiet:
                print("\n".join(lines))


if __name__ == "__main__":
    main()
