#!/usr/bin/env python3
"""Moves function prototypes out of implementer-named headers (decls_b2.h, a_decls.h, ...) into the header of the
module that defines each function (include/<dirs>/<module>_api.h), or into engine/functions.h when no source file
defines it yet. A prototype stays where it is when it uses types the target header does not know, or when the target
already declares the function differently. Files that included the old header get the new headers they need; a header
left with nothing but its guard and includes is deleted and its includes are passed on to its users.
usage: dissolve_headers.py HEADER... [--dry]
"""
import re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
import defs

ROOT = Path(__file__).parent.parent
DRY = "--dry" in sys.argv
PROTO = re.compile(r'^(?P<ext>extern "C" )?(?P<ret>[A-Za-z_][\w\s\*]*?)\b(?P<name>\w+)\s*\((?P<params>[^()]*)\)\s*;\s*(?://.*)?$')
TYPES = {"void", "char", "short", "int", "long", "unsigned", "signed", "const", "volatile", "bool", "float", "double",
         "struct", "u8", "u16", "u32", "u64", "s8", "s16", "s32", "s64", "f32", "BOOL", "Entity", "EntityFunc",
         "FixedPoint", "size_t", "OBJ_WORK_", "PlayerData", "PL_WORK_"}


def type_words(ret, params):
    words = re.findall(r"[A-Za-z_]\w*", ret)
    for p in params.split(","):
        toks = re.findall(r"[A-Za-z_]\w*", p)
        if len(toks) >= 2 and re.search(r"\w\s*$", p.strip()) and not p.strip().endswith("*"):
            toks = toks[:-1]
        words += toks
    return [w for w in words if w != "extern"]


def norm(ret, params):
    ps = []
    for p in params.split(","):
        toks = re.findall(r"[A-Za-z_]\w*|\*", p)
        if len([t for t in toks if t != "*"]) >= 2 and toks[-1] != "*":
            toks = toks[:-1]
        ps.append(" ".join(toks))
    return " ".join(re.findall(r"[A-Za-z_]\w*|\*", ret)) + "(" + ",".join(ps) + ")"


def c_spans(text):
    spans = []
    for m in re.finditer(r'extern "C" \{', text):
        depth, i = 1, m.end()
        while depth and i < len(text):
            depth += {"{": 1, "}": -1}.get(text[i], 0)
            i += 1
        spans.append((m.start(), i))
    return spans


definer = {}
for p in sorted(q for q in (ROOT / "src").rglob("*.cpp") if "wip" not in q.parts):
    for _, n in defs.def_starts(p.read_text(encoding="utf-8").split("\n")):
        definer.setdefault(n, p)


def target_for(name):
    src = definer.get(name)
    if src is None:
        return "engine/functions.h"
    rel = src.parent.relative_to(ROOT / "src").as_posix()
    return f"{rel}/{re.sub(r'_[0-9]+$', '', src.stem)}_api.h"


def declared(header, name):
    """(normalized prototype, is C) of name in header, or None."""
    path = ROOT / "include" / header
    if not path.exists():
        return None
    text = path.read_text(encoding="utf-8")
    spans = c_spans(text)
    for m in re.finditer(r"^(.*?\b%s\s*\(([^()]*)\)\s*;)" % re.escape(name), text, re.M):
        line = m.group(1)
        pm = PROTO.match(line.strip())
        if pm:
            c = bool(pm["ext"]) or any(a <= m.start() < b for a, b in spans)
            return norm(pm["ret"], pm["params"]), c
    return None


def add_to(header, line, c_linkage):
    path = ROOT / "include" / header
    if not path.exists():
        guard = re.sub(r"\W", "_", header).upper()
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(f'#ifndef {guard}\n#define {guard}\n\n#include "engine/entity.h"\n\n#endif\n', encoding="utf-8", newline="\n")
    text = path.read_text(encoding="utf-8")
    if c_linkage:
        if 'extern "C" {' in text:
            i = text.index("\n}", text.index('extern "C" {'))
            text = text[:i] + "\n" + line + text[i:]
        else:
            i = text.rindex("#endif")
            text = text[:i] + 'extern "C" {\n' + line + "\n}\n\n" + text[i:]
    else:
        i = text.rindex("#endif")
        text = text[:i] + line + "\n\n" + text[i:]
    path.write_text(re.sub(r"\n{3,}", "\n\n", text), encoding="utf-8", newline="\n")


# how many headers and source files mention each name as a declaration (a prototype moves only when its header is
# the one place that declares it, so no other declaration can disagree with the new one)
decl_count = {}
for f in list((ROOT / "include").rglob("*.h")) + list((ROOT / "src").rglob("*.cpp")):
    if "wip" in f.parts:
        continue
    for n in set(re.findall(r"\b(\w+)\s*\([^(){};]*\)\s*;", f.read_text(encoding="utf-8", errors="replace"))):
        decl_count[n] = decl_count.get(n, 0) + 1

moved_total = 0
for hpath in [Path(a) for a in sys.argv[1:] if a != "--dry"]:
    hrel = hpath.relative_to(ROOT / "include").as_posix() if hpath.is_absolute() else Path(hpath).relative_to("include").as_posix()
    full = ROOT / "include" / hrel
    text = full.read_text(encoding="utf-8")
    spans = c_spans(text)
    lines = text.split("\n")
    offs, o = [], 0
    for l in lines:
        offs.append(o)
        o += len(l) + 1
    drop, moved = set(), {}
    for i, l in enumerate(lines):
        pm = PROTO.match(l.strip())
        if not pm or l.startswith(("#", "typedef")):
            continue
        name = pm["name"]
        if name in ("if", "while", "return", "sizeof"):
            continue
        c = bool(pm["ext"]) or any(a <= offs[i] < b for a, b in spans)
        if any(w not in TYPES for w in type_words(pm["ret"], pm["params"])):
            continue
        if decl_count.get(name, 0) > 1:
            continue
        tgt = target_for(name)
        if tgt == hrel:
            continue
        have = declared(tgt, name)
        key = norm(pm["ret"], pm["params"])
        if have is not None and have != (key, c):
            continue  # the target declares it differently; fix by hand
        decl = re.sub(r'^extern "C" ', "", l.strip())
        if not DRY and have is None:
            add_to(tgt, decl, c)
        drop.add(i)
        moved[name] = tgt
    moved_total += len(drop)
    print(f"{hrel}: {len(drop)} prototypes moved")
    if DRY or not drop:
        continue
    rest = [l for i, l in enumerate(lines) if i not in drop]
    rest_text = re.sub(r'extern "C" \{\s*\}\n?', "", "\n".join(rest))
    full.write_text(re.sub(r"\n{3,}", "\n\n", rest_text), encoding="utf-8", newline="\n")
    # users: include the headers that now hold the names they use
    own_incs = re.findall(r'^#include "([^"]+)"', rest_text, re.M)
    body = re.sub(r"#ifndef \w+|#define \w+|#endif|#include \"[^\"]+\"|//[^\n]*|\s", "", rest_text)
    empty = body == ""
    for u in list((ROOT / "src").rglob("*.cpp")) + list((ROOT / "include").rglob("*.h")):
        t = u.read_text(encoding="utf-8")
        if f'#include "{hrel}"' not in t:
            continue
        need = sorted({h for n, h in moved.items() if re.search(rf"\b{n}\b", t)} | (set(own_incs) if empty else set()))
        new = [f'#include "{h}"' for h in need if f'#include "{h}"' not in t and u != ROOT / "include" / h]
        if empty:
            t = t.replace(f'#include "{hrel}"\n', "\n".join(new) + ("\n" if new else ""), 1)
        elif new:
            t = t.replace(f'#include "{hrel}"\n', f'#include "{hrel}"\n' + "\n".join(new) + "\n", 1)
        u.write_text(t, encoding="utf-8", newline="\n")
    if empty:
        full.unlink()
        print(f"  {hrel} is empty now and was removed")
print(f"{moved_total} prototypes moved in total")
