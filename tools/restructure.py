#!/usr/bin/env python3
"""One-off move of src/Unknown and include/Unknown into the agreed layout (see docs/naming.md)."""
import re, subprocess
from pathlib import Path
ROOT = Path(__file__).parent.parent
def kind_dir(path: Path) -> str:
    n = path.stem.lower()
    parent = path.parent.name
    if n.startswith("boss"): return "boss"
    if n.startswith(("enemy", "actor", "func_")): return "enemy"
    if n.startswith(("object", "event", "pathmover")): return "object"
    if n.startswith("state"): return "game"
    if n.startswith(("misc", "common")): return "engine"
    if n in ("entity", "player"): return "engine"
    return "misc"
moves = {}
for f in sorted((ROOT / "src/Unknown").rglob("*.c")):
    stem = f.stem.lower().replace("actor_", "enemy_").replace("func_", "enemy_")
    moves[f] = ROOT / "src" / kind_dir(f) / f"{stem}.c"
for h in sorted((ROOT / "include/Unknown").rglob("*.h")):
    moves[h] = ROOT / "include" / kind_dir(h) / f"{h.stem.lower()}.h"
# include path rewrites: "Unknown/X.h" or "Unknown/L/X.h" -> new
inc_map = {str(old.relative_to(ROOT / "include")).replace("\\", "/"): str(new.relative_to(ROOT / "include")).replace("\\", "/")
           for old, new in moves.items() if old.suffix == ".h"}
assert len(set(moves.values())) == len(moves), "name collision"
for old, new in moves.items():
    new.parent.mkdir(parents=True, exist_ok=True)
    tracked = subprocess.run(["git", "ls-files", "--error-unmatch", str(old)], cwd=ROOT, capture_output=True).returncode == 0
    if tracked:
        subprocess.run(["git", "mv", str(old), str(new)], cwd=ROOT, check=True)
    else:
        old.rename(new)
for f in list((ROOT / "src").rglob("*.c")) + list((ROOT / "include").rglob("*.h")):
    s = f.read_text(); t = s
    for o, n in inc_map.items():
        t = t.replace(f'#include "{o}"', f'#include "{n}"')
    if t != s: f.write_text(t)
d = ROOT / "config/eur/arm9/delinks.txt"
s = d.read_text()
for old, new in moves.items():
    if old.suffix == ".c":
        s = s.replace(str(old.relative_to(ROOT)).replace("\\", "/") + ":", str(new.relative_to(ROOT)).replace("\\", "/") + ":")
d.write_text(s, newline="\n")
for left in sorted((ROOT / "src/Unknown").rglob("*"), reverse=True) + sorted((ROOT / "include/Unknown").rglob("*"), reverse=True):
    if left.is_dir() and not any(left.iterdir()): left.rmdir()
print(f"moved {len(moves)} files")
