#!/usr/bin/env python3
"""Moves structs that several source files define identically into one module header.

For each `typedef struct Name { ... } Name;` found identically (ignoring comments and spacing) in two or more files,
the definition goes into include/<dir>/<module>.h (created if missing; <module> is the first file's name without its
_N suffix) and every file includes that header instead. Each move is checked with trymatch on the files it touches
and undone if any of them stops compiling or matching.
usage: hoist_structs.py [--skip FILE ...]
"""
import collections, os, re, subprocess, sys
from pathlib import Path

ROOT = Path(__file__).parent.parent
skip = {Path(a).as_posix() for a in sys.argv[1:] if a != "--skip"}
STRUCT = re.compile(r"(?:^//[^\n]*\n)*^typedef struct (\w+) \{.*?^\} \1;[^\n]*\n", re.S | re.M)


def norm(s):
    return re.sub(r"\s+", " ", re.sub(r"//[^\n]*", "", s)).strip()


def matches(path):
    r = subprocess.run([sys.executable, str(ROOT / "tools/trymatch.py"), str(path), "-q"], capture_output=True, text=True)
    m = re.search(r"(\d+) match, (\d+) differ", r.stdout)
    return bool(m) and m.group(2) == "0" and int(m.group(1)) > 0


found = collections.defaultdict(list)
for p in sorted((ROOT / "src").glob("*/*.cpp")):
    if p.relative_to(ROOT).as_posix() in skip:
        continue
    for m in STRUCT.finditer(p.read_text(encoding="utf-8")):
        found[m.group(1)].append((p, m.group(0)))

done = 0
for name, defs in sorted(found.items()):
    if len(defs) < 2 or len({norm(d) for _, d in defs}) != 1:
        continue
    first = defs[0][0]
    module = re.sub(r"_\d+$", "", first.stem)
    header = ROOT / "include" / first.parent.name / f"{module}.h"
    inc = f'#include "{first.parent.name}/{module}.h"'
    saved = {p: p.read_text(encoding="utf-8") for p, _ in defs}
    saved_h = header.read_text(encoding="utf-8") if header.exists() else None
    best = max((d for _, d in defs), key=len)  # the copy with the most comments
    if saved_h is None:
        guard = f"{first.parent.name}_{module}_H".upper()
        text = f'#ifndef {guard}\n#define {guard}\n\n#include "engine/entity.h"\n\n{best}\n#endif\n'
    else:
        text = saved_h[:saved_h.rindex("#endif")].rstrip("\n") + "\n\n" + best + "\n#endif\n"
    header.write_text(text, encoding="utf-8", newline="\n")
    for p, d in defs:
        t = saved[p].replace(d, "", 1)
        if inc not in t:
            lines = t.split("\n")
            last = max(i for i, l in enumerate(lines) if l.startswith("#include"))
            lines.insert(last + 1, inc)
            t = "\n".join(lines)
        p.write_text(re.sub(r"\n{3,}", "\n\n", t), encoding="utf-8", newline="\n")
    if all(matches(p) for p, _ in defs):
        done += 1
        print(f"{name}: {len(defs)} files -> {header.relative_to(ROOT).as_posix()}")
    else:
        for p, t in saved.items():
            p.write_text(t, encoding="utf-8", newline="\n")
        if saved_h is None:
            header.unlink()
        else:
            header.write_text(saved_h, encoding="utf-8", newline="\n")
        print(f"{name}: undone (does not compile or match)")
print(f"{done} structs moved")
