#!/usr/bin/env python3
"""Reports compiled functions whose size differs from the original (trymatch only compares the compiled bytes)."""
import re, subprocess, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
from sdk_sigmatch import extract_functions
ROOT = Path(__file__).parent.parent
syms = {}
for l in (ROOT / "config/eur/arm9/symbols.txt").read_text().splitlines():
    m = re.match(r"\S+ kind:function\((?:arm|thumb),size=0x([0-9a-f]+)[^)]*\) addr:0x([0-9a-f]+)", l)
    if m: syms[int(m.group(2), 16)] = int(m.group(1), 16)
flags = "-O4,p -enum int -char signed -str noreuse -proc arm946e -gccext,on -fp soft -inline noauto -Cpp_exceptions off -RTTI off -interworking -w off -sym on -gccinc -nolink -ipa file".split()
files = [Path(a) for a in sys.argv[1:]] or sorted((ROOT / "src").rglob("*.c*"))
bad = 0
for f in files:
    out = ROOT / "scratch/size_check.o"
    lang = "-lang=c++" if f.suffix == ".cpp" else "-lang=c99"
    subprocess.run([str(ROOT / "tools/mwccarm/dsi/1.2/mwccarm.exe"), *flags, lang, "-i", str(ROOT / "include"), "-c", str(f), "-o", str(out)], capture_output=True)
    for name, thumb, code, mask in extract_functions(out.read_bytes()):
        m = re.search(r"([0-9a-f]{8})", name)
        if m and syms.get(int(m.group(1), 16)) != len(code):
            bad += 1
            print(f"{f}: {name} compiled {len(code):#x} original {syms.get(int(m.group(1), 16), 0):#x}")
print(f"{bad} size mismatches")
