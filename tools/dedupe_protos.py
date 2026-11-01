#!/usr/bin/env python3
"""Removes `extern "C"` prototypes from source files when a header already declares the same function with C linkage
and the same types and the file already includes that header. Run, rebuild, and check the ROM. usage: dedupe_protos.py [--dry]
"""
import collections, re, sys
from pathlib import Path

ROOT = Path(__file__).parent.parent
DRY = "--dry" in sys.argv
PROTO = re.compile(r'^extern "C" (?!\{)(?P<ret>[^()]*?)\b(?P<name>\w+)\s*\((?P<params>[^()]*)\)\s*;\s*(?://.*)?$')
HDECL = re.compile(r'^(?:extern "C" )?(?P<ret>[^()#/]*?)\b(?P<name>\w+)\s*\((?P<params>[^()]*)\)\s*;', re.M)


def norm(ret, params):
    out = []
    if params.strip() not in ("", "void"):
        for p in params.split(","):
            toks = re.findall(r"[A-Za-z_]\w*|\*|&|\[\s*\w*\s*\]|\.\.\.", p)
            if len([t for t in toks if re.match(r"\w", t)]) >= 2 and re.match(r"\w", toks[-1]):
                toks = toks[:-1]
            out.append(" ".join(toks))
    ret = [t for t in re.findall(r"[A-Za-z_]\w*|\*|&", ret) if t != "extern"]
    return " ".join(ret) + "(" + ",".join(out) + ")"


def c_linkage_spans(text):
    """Character ranges of `extern "C" { ... }` blocks."""
    spans = []
    for m in re.finditer(r'extern "C" \{', text):
        depth, i = 1, m.end()
        while depth and i < len(text):
            depth += {"{": 1, "}": -1}.get(text[i], 0)
            i += 1
        spans.append((m.start(), i))
    return spans


# name -> {normalized: header}; only C-linkage declarations, outside namespaces
hdecl = collections.defaultdict(dict)
bad = set()
for h in sorted((ROOT / "include").rglob("*.h")):
    if "wip" in h.parts:
        continue
    text = h.read_text(encoding="utf-8", errors="replace")
    if "namespace" in text:
        continue
    spans = c_linkage_spans(text)
    rel = h.relative_to(ROOT / "include").as_posix()
    for m in HDECL.finditer(text):
        c = m.group(0).startswith('extern "C"') or any(a <= m.start() < b for a, b in spans)
        key = norm(m["ret"], m["params"])
        if not c:
            bad.add(m["name"])
        elif key in hdecl[m["name"]]:
            continue
        else:
            hdecl[m["name"]][key] = rel

removed = 0
for p in sorted(q for q in (ROOT / "src").rglob("*.cpp") if "wip" not in q.parts):
    lines = p.read_text(encoding="utf-8").split("\n")
    if any(l.startswith("namespace") for l in lines):
        continue
    drop, incs = set(), set()
    for i, l in enumerate(lines):
        m = PROTO.match(l)
        if not m or m["name"] in bad or len(hdecl.get(m["name"], {})) != 1:
            continue
        key = norm(m["ret"], m["params"])
        h = hdecl[m["name"]].get(key)
        if h is not None and f'#include "{h}"' in lines:  # only headers the file already includes
            drop.add(i)
            incs.add(h)
    if not drop:
        continue
    removed += len(drop)
    if DRY:
        continue
    out = [l for i, l in enumerate(lines) if i not in drop]
    new = [f'#include "{h}"' for h in sorted(incs) if f'#include "{h}"' not in out]
    if new:
        last = max((i for i, l in enumerate(out) if l.startswith("#include")), default=-1)
        out[last + 1:last + 1] = new
    p.write_text(re.sub(r"\n{3,}", "\n\n", "\n".join(out)), encoding="utf-8", newline="\n")
print(f"removed {removed} prototype lines")
