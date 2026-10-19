#!/usr/bin/env python3
"""Moves every shared function prototype into include/engine/functions.h with one consistent declaration.

C++ treats prototypes with different parameter types as different functions, so scattered declarations that
disagree (int vs s32, u8 vs int) break linking. For each function this picks one declaration:
- original C++ signature from config/eur/original_names.tsv when the debug build has one (parameter types),
  return type and parameter names from the existing declarations;
- `extern "C"` when the original name was not mangled, or the function is a TwlSDK one;
- otherwise the most common existing declaration.
Prototypes that use file-local types stay where they are. Run once; review the diff.
"""
import collections, json, re
from pathlib import Path

ROOT = Path(__file__).parent.parent
OUT = ROOT / "include/engine/functions.h"

GLOBAL_TYPES = {"void", "char", "short", "int", "long", "unsigned", "signed", "const", "bool", "u8", "u16", "u32",
                "u64", "s8", "s16", "s32", "s64", "f32", "BOOL", "Entity", "PlayerData", "EntityFunc", "FixedPoint",
                "struct", "OBJ_WORK_", "PL_WORK_", "volatile", "size_t", "float", "double"}
PROTO = re.compile(r"^(?:extern\s+)?(?P<ret>(?:const\s+)?[A-Za-z_]\w*(?:\s+[A-Za-z_]\w*)*\s*\**)\s*\b(?P<name>[A-Za-z_]\w*)"
                   r"\s*\((?P<params>[^;{}()]*)\)\s*;[ \t]*(?://.*)?$", re.M)
TYPEMAP = {"OBJ_WORK_*": "Entity *", "PL_WORK_*": "PlayerData *", "unsigned char": "u8", "unsigned short": "u16",
           "unsigned long": "u32", "long": "s32", "short": "s16", "signed char": "s8", "char": "char", "int": "int",
           "unsigned int": "unsigned int", "bool": "bool", "void": "void", "unsigned long long": "u64",
           "long long": "s64", "float": "f32"}


def words(decl):
    return set(re.findall(r"[A-Za-z_]\w*", decl))


def split_params(params):
    params = params.strip()
    if params in ("", "void"):
        return []
    return [p.strip() for p in params.split(",")]


def param_name(p):
    m = re.search(r"([A-Za-z_]\w*)\s*(\[\s*\w*\s*\])?$", p)
    if m and m.group(1) not in GLOBAL_TYPES and not re.fullmatch(r"u8|u16|u32|s8|s16|s32|int|long|char", m.group(1)):
        return m.group(1)
    return None


def demangled_params(sig):
    """Parameter types from a c++filt signature `name(type, type)`; None if the original is extern "C"."""
    if "(" not in sig:
        return None
    inner = sig[sig.index("(") + 1:sig.rindex(")")]
    if inner.strip() in ("", "void"):
        return []
    out = []
    depth, cur = 0, ""
    for ch in inner:
        if ch == "," and depth == 0:
            out.append(cur.strip()); cur = ""
            continue
        depth += ch in "(<"; depth -= ch in ")>"
        cur += ch
    out.append(cur.strip())
    res = []
    for t in out:
        const = t.startswith("const ") or " const" in t
        base = t.replace("const", "").strip()
        ptr = base.count("*")
        core = base.replace("*", "").strip()
        if core + "*" in TYPEMAP and ptr:
            mapped = TYPEMAP[core + "*"].rstrip("*").strip(); ptr -= 1; mapped += " *"
        elif core in TYPEMAP:
            mapped = TYPEMAP[core]
        else:
            mapped = core  # another struct type
        res.append(("const " if const else "") + mapped + (" " + "*" * ptr if ptr else ""))
    return res


def main():
    orig = {}
    for line in (ROOT / "config/eur/original_names.tsv").read_text().splitlines():
        if line.startswith("#"):
            continue
        addr, name, sig = line.split("\t")
        orig[name] = sig
    sdk = {json.loads(l)["name"] for l in (ROOT / "config/eur/sdk_matches.jsonl").read_text().splitlines() if l.strip()}

    files = sorted(ROOT.glob("include/**/*.h")) + sorted(ROOT.glob("src/**/*.cpp"))
    files = [f for f in files if f != OUT and "wip" not in f.parts]
    decls = collections.defaultdict(list)  # name -> [(file, ret, params, line)]
    for f in files:
        text = f.read_text(encoding="utf-8")
        for m in PROTO.finditer(text):
            line = m.group(0)
            if line.lstrip().startswith(("return", "typedef", "static", "else")) or "(*" in line:
                continue
            ret, name, params = m.group("ret").strip(), m.group("name"), m.group("params")
            if not words(ret + " " + params) <= GLOBAL_TYPES | {p for p in (param_name(x) for x in split_params(params)) if p}:
                continue
            decls[name].append((f, ret, params, line))

    header, moved = [], collections.defaultdict(set)
    c_names, cpp_lines = [], []
    for name in sorted(decls):
        ds = decls[name]
        ret = collections.Counter(re.sub(r"\s+", " ", d[1]).replace(" *", "*").replace("*", " *") for d in ds).most_common(1)[0][0]
        variants = collections.Counter(tuple(split_params(d[2])) for d in ds)
        params = list(variants.most_common(1)[0][0])
        sig = orig.get(name)
        original_types = demangled_params(sig) if sig and "::" not in sig else None
        if original_types is not None:
            names = None
            for v in variants:
                if len(v) == len(original_types):
                    names = [param_name(p) for p in v]
                    break
            params = [t + ((" " if not t.endswith("*") else "") + n if n else "") for t, n in
                      zip(original_types, names or [None] * len(original_types))]
            if any(not (words(t) <= GLOBAL_TYPES) for t in original_types):
                extra = {w for t in original_types for w in words(t)} - GLOBAL_TYPES
                header.extend(f"struct {w};" for w in sorted(extra))
        decl = f"{ret}{'' if ret.endswith('*') else ' '}{name}({', '.join(params) if params else 'void'});"
        # Unmangled originals and TwlSDK are C. Class methods are declared as plain C functions for now.
        is_c = (sig is not None and ("(" not in sig or "::" in sig.split("(")[0])) or name in sdk
        (c_names if is_c else cpp_lines).append(decl)
        for d in ds:
            moved[d[0]].add(d[3])

    lines = ["#ifndef ENGINE_FUNCTIONS_H", "#define ENGINE_FUNCTIONS_H", "",
             "// Shared function prototypes, one declaration per function. Generated by tools/gen_functions_h.py, then",
             "// maintained by hand. Parameter types follow the original C++ signatures from the debug build where known",
             "// (config/eur/original_names.tsv); extern \"C\" functions were unmangled in the original or are TwlSDK.", "",
             '#include "engine/entity.h"', '#include "engine/player.h"', ""]
    lines += sorted(set(header)) + [""] if header else []
    lines += ['extern "C" {'] + c_names + ["}", ""] + cpp_lines + ["", "#endif", ""]
    OUT.write_text("\n".join(lines), newline="\n")

    for f, ls in moved.items():
        text = f.read_text(encoding="utf-8")
        for l in ls:
            text = text.replace(l + "\n", "", 1)
        if f.suffix == ".cpp" and '#include "engine/functions.h"' not in text:
            text = '#include "engine/functions.h"\n' + text
        f.write_text(text, encoding="utf-8", newline="\n")
    for f in ROOT.glob("src/**/*.cpp"):
        text = f.read_text(encoding="utf-8")
        if '#include "engine/functions.h"' not in text:
            f.write_text('#include "engine/functions.h"\n' + text, encoding="utf-8", newline="\n")
    print(f"{len(decls)} functions: {len(c_names)} extern \"C\", {len(cpp_lines)} C++; {len(moved)} files edited")


if __name__ == "__main__":
    main()
