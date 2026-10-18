#!/usr/bin/env python3
"""Renames a field of a shared struct and every access to it, checked by compiling every integrated file.

usage: rename_field.py HEADER OLD NEW
Accesses (->OLD / .OLD) are renamed everywhere, then each file is compiled; any occurrence that turns out to belong to
a different struct (compile error) is put back. Fails if a file can't be made to compile.
"""
import re, subprocess, sys
from pathlib import Path
ROOT = Path(__file__).parent.parent
header, old, new = Path(sys.argv[1]), sys.argv[2], sys.argv[3]
CC = str((ROOT / "tools/mwccarm/dsi/1.2/mwccarm.exe").resolve())
FLAGS = "-O4,p -enum int -char signed -str noreuse -proc arm946e -gccext,on -fp soft -inline noauto -Cpp_exceptions off -RTTI off -interworking -w off -sym on -gccinc -nolink -ipa file -lang=c99".split()
h = header.read_text()
h2 = re.sub(rf"(\*/ [^;\n]*?)\b{old}\b(\s*[;\[])", rf"\1{new}\2", h)
if h2 == h: sys.exit(f"{old} not defined in {header}")
header.write_text(h2)
delinks = (ROOT / "config/eur/arm9/delinks.txt").read_text()
units = [ROOT / u for u in re.findall(r"^(src/\S+\.c):$", delinks, re.M)]
for f in list((ROOT / "src").rglob("*.c")) + list((ROOT / "include").rglob("*.h")):
    s = f.read_text(); t = re.sub(rf"(->|\.){old}\b", rf"\g<1>{new}", s)
    if t != s: f.write_text(t)
def errors(f):
    r = subprocess.run([CC, *FLAGS, "-i", str(ROOT / "include"), "-c", str(f), "-o", str(ROOT / "scratch/rf.o")], capture_output=True, text=True)
    errs = []
    for block in (r.stdout + r.stderr).split("### mwccarm.exe Compiler:"):
        m = re.search(r"#\s+(?:File|In): (\S+)", block); n = re.search(r"#\s+(\d+): ", block)
        if m and n: errs.append((ROOT / m.group(1).replace(chr(92), "/"), int(n.group(1))))
    return r.returncode, errs
for f in units:
    for _ in range(200):
        rc, errs = errors(f)
        if rc == 0: break
        if not errs: sys.exit(f"{f}: unparsed compile error")
        p, line = errs[0]
        lines = p.read_text().split("\n")
        L = lines[line - 1]
        occ = list(re.finditer(rf"(->|\.){new}\b", L))
        if not occ: sys.exit(f"{p}:{line}: error not caused by the rename: {L.strip()}")
        m = occ[-1]
        lines[line - 1] = L[:m.start()] + m.group(1) + old + L[m.end():]
        p.write_text("\n".join(lines))
    else:
        sys.exit(f"{f}: too many errors")
print(f"renamed {old} -> {new}; all {len(units)} units compile")
