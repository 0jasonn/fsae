#!/usr/bin/env python3
"""Moves an implementer's finished work into the tree and adds the units.

usage: integrate_wip.py LETTER DEST   (DEST is enemy, object, game or engine)

- applies the lines of scratch/agent<L>/renames.txt whose old name still exists in symbols.txt
- moves src/wip/<L>/*.cpp to src/<DEST>/ and include/wip/<L>/*.h to include/<DEST>/ (refuses to overwrite)
- rewrites "wip/<L>/x.h" includes, replaces stale dsd names, and runs integrate.py on every moved file
Then run tools/build_commit.sh.
"""
import re, subprocess, sys
from pathlib import Path

ROOT = Path(__file__).parent.parent
letter, dest = sys.argv[1], sys.argv[2]
py = sys.executable

names = {l.split(" ", 1)[0] for l in (ROOT / "config/eur/arm9/symbols.txt").read_text().splitlines()}
ren = ROOT / f"scratch/agent{letter}/renames.txt"
lines = [l for l in ren.read_text().splitlines() if len(l.split()) == 2 and l.split()[0] in names
         and l.split()[1] not in names] if ren.exists() else []
lines = list(dict.fromkeys(lines))
if lines:
    tmp = ROOT / f"scratch/integrate_{letter}_renames.txt"
    tmp.write_text("\n".join(lines) + "\n", newline="\n")
    subprocess.run([py, str(ROOT / "tools/apply_renames.py"), str(tmp)], check=True, capture_output=True)
    print(f"applied {len(lines)} renames")

moved = []
for kind, ext in (("src", "*.cpp"), ("include", "*.h")):
    for f in sorted((ROOT / kind / "wip" / letter).glob(ext)):
        target = ROOT / kind / dest / f.name
        if target.exists():
            sys.exit(f"{target} already exists; rename {f} first")
        target.parent.mkdir(parents=True, exist_ok=True)
        f.rename(target)
        moved.append(target)

for f in list((ROOT / "src").rglob("*.cpp")) + list((ROOT / "include").rglob("*.h")):
    if "wip" in f.parts:
        continue
    s = f.read_text(encoding="utf-8")
    t = s.replace(f'"wip/{letter}/', f'"{dest}/')
    if t != s:
        f.write_text(t, encoding="utf-8", newline="\n")

subprocess.run([py, str(ROOT / "tools/fix_stale_names.py")], check=True)
for f in moved:
    if f.suffix == ".cpp":
        r = subprocess.run([py, str(ROOT / "tools/integrate.py"), str(f.relative_to(ROOT).as_posix())],
                           cwd=ROOT, capture_output=True, text=True)
        print("\n".join(l for l in r.stdout.splitlines() if "funcs" in l or "order" in l))
