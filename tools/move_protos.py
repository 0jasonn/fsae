#!/usr/bin/env python3
"""Moves the `extern "C"` prototypes that source files declare for themselves into shared headers.

For every function declared `extern "C" <ret> name(<params>);` in a source file (one line, plain or Entity-like types
only, the same prototype everywhere it is declared):
- a function defined in src/<dir>/<module>[_N].cpp goes into include/<dir>/<module>_api.h, inside `extern "C" { }`;
- a function nobody defines yet goes into include/engine/functions.h's extern "C" block.
The source lines are removed and the files that declared them include the new headers. Prototypes that use other
types, function pointers or that disagree between files stay where they are. Run, rebuild, and check the ROM.
usage: move_protos.py [--dry]
"""
import collections, re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
import defs

ROOT = Path(__file__).parent.parent
DRY = "--dry" in sys.argv
PROTO = re.compile(r'^extern "C" (?!\{)(?P<decl>(?P<ret>[^()]*?)\b(?P<name>\w+)\s*\((?P<params>[^()]*)\)\s*;)\s*(?://.*)?$')
KEYWORDS = {"const", "volatile", "unsigned", "signed", "struct", "void", "char", "short", "int", "long", "bool",
            "float", "double"}


def known_types():
    """Type names usable in a header that includes types.h and engine/entity.h."""
    names = set()
    for h in ("include/types.h", "include/engine/entity.h"):
        text = (ROOT / h).read_text(encoding="utf-8")
        names |= set(re.findall(r"typedef\s+[^;{]*?\b(\w+)\s*;", text))
        names |= set(re.findall(r"\}\s*(\w+)\s*;", text))  # typedef struct {...} Name;
        names |= set(re.findall(r"^(?:struct|class)\s+(\w+)", text, re.M))
    return names


TYPES = known_types() | KEYWORDS


def type_words(params, ret):
    """Identifiers of the types in a prototype (parameter names dropped), or None if it cannot be parsed."""
    words = re.findall(r"[A-Za-z_]\w*", ret)
    if params.strip() not in ("", "void"):
        for p in params.split(","):
            p = p.strip()
            if p == "...":
                continue
            toks = re.findall(r"[A-Za-z_]\w*|\*|&|\[\s*\w*\s*\]", p)
            if len([t for t in toks if re.match(r"\w", t)]) >= 2 and re.match(r"\w", toks[-1]):
                toks = toks[:-1]  # parameter name
            words += [t for t in toks if re.match(r"[A-Za-z_]", t)]
    return words


def norm(ret, params):
    out = []
    if params.strip() not in ("", "void"):
        for p in params.split(","):
            toks = re.findall(r"[A-Za-z_]\w*|\*|&|\[\s*\w*\s*\]|\.\.\.", p)
            if len([t for t in toks if re.match(r"\w", t)]) >= 2 and re.match(r"\w", toks[-1]):
                toks = toks[:-1]
            out.append(" ".join(toks))
    return " ".join(re.findall(r"[A-Za-z_]\w*|\*|&", ret)) + "(" + ",".join(out) + ")"


sources = sorted(p for p in (ROOT / "src").glob("*/*.cpp") if p.parent.name != "wip")
definer = {}
for p in sources:
    for _, n in defs.def_starts(p.read_text(encoding="utf-8").split("\n")):
        definer.setdefault(n, p)

decls = collections.defaultdict(list)  # name -> [(path, line index, decl text, normalized)]
other_decl = set()  # names some source declares another way (inside extern "C" { }, C++ linkage, in a namespace)
for p in sources:
    lines = p.read_text(encoding="utf-8").split("\n")
    in_ns = any(l.startswith("namespace") for l in lines)
    for i, l in enumerate(lines):
        m = PROTO.match(l)
        if m and not in_ns:
            decls[m["name"]].append((p, i, m["decl"].strip(), norm(m["ret"], m["params"])))
        else:
            d = re.match(r"^\s*(?:extern \"C\" )?[A-Za-z_][\w\s\*&:<>]*?\b(\w+)\s*\([^{}]*\)\s*;", l)
            if d:
                other_decl.add(d.group(1))

funcs_h = (ROOT / "include/engine/functions.h").read_text(encoding="utf-8")
# names any header already declares (moving those could clash with the header's version)
in_headers = set()
for h in (ROOT / "include").rglob("*.h"):
    if "wip" not in h.parts:
        in_headers |= set(re.findall(r"\b(\w+)\s*\(", h.read_text(encoding="utf-8", errors="replace")))
headers = collections.defaultdict(list)  # header path -> [decl]
remove = collections.defaultdict(set)    # source -> line indexes
needs = collections.defaultdict(set)     # source -> headers to include
kept = 0
for name, ds in sorted(decls.items()):
    words = []
    for d in ds:
        m = PROTO.match('extern "C" ' + d[2])
        words += type_words(m["params"], m["ret"])
    if len({d[3] for d in ds}) != 1 or any(w not in TYPES for w in words) or name in in_headers \
            or name in other_decl:
        kept += len(ds)
        continue
    src = definer.get(name)
    if src is not None:
        module = re.sub(r"_\d+$", "", src.stem)
        header = f"{src.parent.name}/{module}_api.h"
    else:
        header = "engine/functions.h"
    headers[header].append(ds[0][2])
    for p, i, _, _ in ds:
        remove[p].add(i)
        if header != "engine/functions.h":
            needs[p].add(header)
    if src is not None:
        needs[src].add(header)

print(f"moving {sum(len(v) for v in remove.values())} prototype lines ({sum(len(v) for v in headers.values())} "
      f"functions) into {len(headers)} headers; {kept} lines stay local")
if DRY:
    sys.exit()

for header, protos in headers.items():
    if header == "engine/functions.h":
        text = (ROOT / "include/engine/functions.h").read_text(encoding="utf-8")
        start = text.index('extern "C" {\n') + len('extern "C" {\n')
        text = text[:start] + "".join(d + "\n" for d in sorted(protos, key=lambda d: PROTO.match('extern "C" ' + d)["name"])) + text[start:]
        (ROOT / "include/engine/functions.h").write_text(text, encoding="utf-8", newline="\n")
        continue
    path = ROOT / "include" / header
    assert not path.exists(), path
    guard = re.sub(r"\W", "_", header).upper()
    module = Path(header).stem[:-4]
    body = "\n".join(protos)
    path.write_text(f"#ifndef {guard}\n#define {guard}\n\n// Functions defined in src/{Path(header).parent}/{module}*.cpp.\n\n"
                    f'#include "engine/entity.h"\n\nextern "C" {{\n{body}\n}}\n\n#endif\n', encoding="utf-8", newline="\n")

for p in sorted(set(remove) | set(needs)):
    lines = p.read_text(encoding="utf-8").split("\n")
    out = [l for i, l in enumerate(lines) if i not in remove[p]]
    incs = [f'#include "{h}"' for h in sorted(needs[p]) if f'#include "{h}"' not in out]
    if incs:
        last = max((i for i, l in enumerate(out) if l.startswith("#include")), default=-1)
        out[last + 1:last + 1] = incs
    text = re.sub(r"\n{3,}", "\n\n", "\n".join(out))
    p.write_text(text, encoding="utf-8", newline="\n")
