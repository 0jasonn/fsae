#!/usr/bin/env python3
"""Stages everything except implementer work in progress: files under src/Unknown/<letter>/ that are not delinks units,
and headers under include/Unknown/<letter>/ that no unit includes."""
import re, subprocess
from pathlib import Path
ROOT = Path(__file__).parent.parent
subprocess.run(["git", "add", "-A"], cwd=ROOT, check=True)
delinks = (ROOT / "config/eur/arm9/delinks.txt").read_text()
units = set(re.findall(r"^(src/\S+):$", delinks, re.M))
included = set()
for u in units:
    p = ROOT / u
    if p.exists():
        included |= set(re.findall(r'#include "([^"]+)"', p.read_text()))
staged = subprocess.run(["git", "diff", "--cached", "--name-only", "--diff-filter=A"], cwd=ROOT, capture_output=True, text=True).stdout.split()
drop = []
for f in staged:
    if f.startswith("src/") and f.endswith((".c", ".cpp")) and f not in units:
        drop.append(f)
    m = re.match(r"include/(Unknown/[A-Z]/.+)", f)
    if m and m.group(1) not in included:
        drop.append(f)
if drop:
    subprocess.run(["git", "reset", "-q", "--", *drop], cwd=ROOT, check=True)
    print(f"left {len(drop)} work-in-progress files unstaged")
