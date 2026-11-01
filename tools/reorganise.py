#!/usr/bin/env python3
"""One-off move of src/ and include/ into subsystem folders (2026-11-01).

Each file goes to a folder chosen from its module name (file name without _N, _api or a one-letter implementer
suffix); git mv keeps history. Include lines, delinks.txt paths and scratch/merge_failed.txt are rewritten.
usage: reorganise.py [--dry]
"""
import re, subprocess, sys
from pathlib import Path

ROOT = Path(__file__).parent.parent
DRY = "--dry" in sys.argv

RULES = [  # (new folder, module-name prefixes or exact names); first match wins
    ("knife/sound", ("knife_sound", "knifesound")),
    ("engine/sound", ("m4a", "snd")),
    ("knife/message", ("textrender", "textreader", "textlength", "texttoken", "texttags", "text_box", "text_stream",
                       "textbox_lookup", "tokens", "ces", "kmsg", "rendertarget", "pictogram", "knife_font",
                       "knife_message", "knife_canvas", "message_localize", "tcl_text", "text_tokenizer", "texttok",
                       "fullwidth", "wstr", "=text", "=textrender", "=texttoken")),
    ("knife/comm", ("comm_", "wireless", "wm_", "=wm", "single_", "singleplay", "knife_comm", "knifecomm",
                    "knife_single", "multisio", "=com", "comfinit", "commerror", "=comm", "wxc", "datalink",
                    "com_sio", "change_buffer")),
    ("knife/app", ("knife_app", "knifeapp", "knife_file", "knife_hud", "knife_interp", "knife_manual", "knife_power",
                   "knifeinfo", "knifesave", "knifetbl", "=twl", "terminateinfo", "bootinfo")),
    ("knife/subtask", ("subtask",)),
    ("ui/widget", ("rect_", "=rect", "ctrl_", "=ctrl", "pane_", "=pane", "slider", "menu_release", "menu_scroll",
                   "tilebuf", "tile_", "window_", "uiobject", "baseduiview", "=menu", "menu_")),
    ("ui", ("fileselui", "nameentry", "lobby", "stagesel", "selectiondialog", "groupselect", "groupcreateui",
            "modeselui", "playstyleselui", "=title", "oplogo", "opening", "opdemo", "staffroll", "doorsel",
            "dialog_machiuke", "msgwin", "messageselect", "=message", "message_", "msgdat")),
]
DIR_DEFAULT = {"enemy": "actor/enemy", "object": "actor/object", "game": "game", "engine": "engine"}


def module(stem):
    s = re.sub(r"_api$", "", stem)
    s = re.sub(r"_\d+$", "", s)
    return s


def folder(old_dir, stem):
    if old_dir in ("enemy", "object"):
        return DIR_DEFAULT[old_dir]
    m = module(stem)
    for new, keys in RULES:
        for k in keys:
            if (k.startswith("=") and m == k[1:]) or (not k.startswith("=") and m.startswith(k)):
                return new
    return DIR_DEFAULT[old_dir]


moves = {}  # old relative path -> new relative path
for top, ext in (("src", "*.cpp"), ("include", "*.h")):
    for p in sorted((ROOT / top).glob(f"*/{ext}")):
        d = p.parent.name
        if d not in DIR_DEFAULT:
            continue
        new = f"{top}/{folder(d, p.stem)}/{p.name}"
        old = p.relative_to(ROOT).as_posix()
        if new != old:
            moves[old] = new

counts = {}
for old, new in moves.items():
    counts[new.rsplit("/", 1)[0]] = counts.get(new.rsplit("/", 1)[0], 0) + 1
for k in sorted(counts):
    print(f"{counts[k]:4} -> {k}")
if DRY:
    sys.exit()

for old, new in moves.items():
    (ROOT / new).parent.mkdir(parents=True, exist_ok=True)
    subprocess.run(["git", "mv", old, new], cwd=ROOT, check=True)

inc = {o[len("include/"):]: n[len("include/"):] for o, n in moves.items() if o.startswith("include/")}
pat = re.compile(r'(#include\s+")([^"]+)(")')
for f in list((ROOT / "src").rglob("*.cpp")) + list((ROOT / "include").rglob("*.h")):
    t = f.read_text(encoding="utf-8")
    t2 = pat.sub(lambda m: m.group(1) + inc.get(m.group(2), m.group(2)) + m.group(3), t)
    if t2 != t:
        f.write_text(t2, encoding="utf-8", newline="\n")

for cfg in (ROOT / "config/eur/arm9/delinks.txt", ROOT / "scratch/merge_failed.txt"):
    if cfg.exists():
        t = cfg.read_text()
        t = re.sub(r"src/\w+/[\w]+\.cpp", lambda m: moves.get(m.group(0), m.group(0)), t)
        cfg.write_text(t, newline="\n")
print(f"moved {len(moves)} files")
