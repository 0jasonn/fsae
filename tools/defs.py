"""Finds function definitions in a source file.

A definition starts at column 0 with its return type (optionally `extern "C"`, `static`, `inline` or `asm`) and
`name(` on the same line, and the first `{` after it comes before any `;` (so multi-line prototypes are skipped).
"""
import re

_HEAD = re.compile(r'^(?:ARM )?(?:extern "C" )?(?:static )?(?:inline )?(?:asm )?(?!(?:return|if|else|while|for|switch|'
                   r'do|case|goto|typedef|struct|union|enum|class|namespace|template|using|extern|sizeof)\b)'
                   r'[A-Za-z_][\w\s\*&:<>,]*?\b(~?\w+(?:::~?\w+)*)\s*\(')


def def_starts(lines):
    """[(line index, name)] of every function definition in `lines`."""
    out = []
    for i, l in enumerate(lines):
        if not l or l[0] in " \t#/}{":
            continue
        m = _HEAD.match(l)
        if not m:
            continue
        rest = "\n".join(lines[i:i + 40])[m.end():]
        brace, semi = rest.find("{"), rest.find(";")
        if brace != -1 and (semi == -1 or brace < semi):
            out.append((i, m.group(1)))
    return out


def def_names(text):
    return [n for _, n in def_starts(text.split("\n"))]
