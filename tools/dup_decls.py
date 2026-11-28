#!/usr/bin/env python3
"""Lists functions and globals declared in more than one place (headers outside include/wip, plus local declarations in
src/ outside src/wip). The rule is one declaration, in the owner header.

usage: python tools/dup_decls.py            list every duplicated name
       python tools/dup_decls.py --new      only names not in scratch/dup_baseline.txt (exit 1 if any)
       python tools/dup_decls.py --baseline write the current list to scratch/dup_baseline.txt
"""
import re, sys
from collections import defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
BASE = ROOT / "scratch/dup_baseline.txt"
# A declaration line: optional extern / extern "C", a return type, a name, a parameter list, ending in ';'.
FUNC = re.compile(r'^\s*(?:extern\s+(?:"C"\s+)?)?(?:const\s+|static\s+|unsigned\s+|struct\s+)*[A-Za-z_][\w:]*[\s\*&]+\**([A-Za-z_]\w*)\s*\([^;{]*\)\s*;')
DATA = re.compile(r'^\s*extern\s+(?:"C"\s+)?(?:const\s+|volatile\s+|struct\s+|unsigned\s+)*[A-Za-z_]\w*[\s\*]+\**([A-Za-z_]\w*)\s*(?:\[[^\]]*\])*\s*;')

def scan():
    where = defaultdict(set)
    files = [p for p in (ROOT / "include").rglob("*.h") if "wip" not in p.parts]
    files += [p for p in (ROOT / "src").rglob("*.cpp") if "wip" not in p.parts]
    for p in files:
        depth = 0
        for line in p.read_text(errors="ignore").split("\n"):
            code = line.split("//")[0]
            if depth == 0 or p.suffix == ".h":
                m = FUNC.match(code) or DATA.match(code)
                if m and not code.lstrip().startswith(("return", "typedef", "#")):
                    where[m.group(1)].add(p.relative_to(ROOT).as_posix())
            depth += code.count("{") - code.count("}")
            depth = max(depth, 0) if p.suffix == ".cpp" else 0
    return {n: sorted(w) for n, w in where.items() if len(w) > 1}

dups = scan()
if "--baseline" in sys.argv:
    BASE.write_text("\n".join(sorted(dups)) + "\n")
    print(f"baseline: {len(dups)} duplicated names")
elif "--new" in sys.argv:
    old = set(BASE.read_text().split()) if BASE.exists() else set()
    new = {n: w for n, w in dups.items() if n not in old}
    for n, w in sorted(new.items()):
        print(f"DUPLICATE {n}: {', '.join(w)}")
    print(f"{len(dups)} duplicated names, {len(new)} new")
    sys.exit(1 if new else 0)
else:
    for n, w in sorted(dups.items()):
        print(f"{n}: {', '.join(w)}")
    print(f"{len(dups)} duplicated names")
