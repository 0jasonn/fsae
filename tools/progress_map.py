#!/usr/bin/env python3
"""Draws the decompilation progress map: every ARM9 function as a block sized by its code size, in address order.

Writes
- docs/progress.svg   static map for the README (consecutive blocks of the same state are merged)
- docs/progress.html  interactive map for GitHub Pages: hover shows name, address, size and file, with a search box
- docs/progress.json  the numbers behind both

States: decompiled (in a C++ unit listed in delinks.txt), library (TwlSDK / runtime, signature-matched, not
decompiled here) and remaining. Run after a successful build; build_commit.sh does this.
"""
import html, json, re
from pathlib import Path

ROOT = Path(__file__).parent.parent
DOCS = ROOT / "docs"
WIDTH, ROW_H, GAP = 960, 12, 2
COLORS = {"decompiled": "#3fb950", "library": "#58a6ff", "remaining": "#30363d"}
LABELS = {"decompiled": "Decompiled (C++)", "library": "TwlSDK / runtime", "remaining": "Not decompiled yet"}


def plain(name):
    m = re.match(r"_Z(\d+)", name)
    return name[len(m.group(0)):len(m.group(0)) + int(m.group(1))] if m else name


def load():
    funcs = []
    for line in (ROOT / "config/eur/arm9/symbols.txt").read_text().splitlines():
        m = re.match(r"(\S+) kind:function\((arm|thumb),size=0x([0-9a-f]+)[^)]*\) addr:0x([0-9a-f]+)", line)
        if m:
            funcs.append([int(m.group(4), 16), int(m.group(3), 16), plain(m.group(1)), m.group(2)])
    funcs.sort()
    for i, f in enumerate(funcs):  # unknown sizes: up to the next function
        if f[1] == 0 and i + 1 < len(funcs):
            f[1] = min(funcs[i + 1][0] - f[0], 0x1000)
    units = []
    delinks = (ROOT / "config/eur/arm9/delinks.txt").read_text()
    for m in re.finditer(r"^(src/\S+\.cpp):\n\s+complete\n\s+\.text\s+start:0x([0-9a-f]+) end:0x([0-9a-f]+)", delinks, re.M):
        units.append((int(m.group(2), 16), int(m.group(3), 16), m.group(1)))
    sdk = {json.loads(l)["address"] for l in (ROOT / "config/eur/sdk_matches.jsonl").read_text().splitlines() if l.strip()}
    out = []
    for addr, size, name, mode in funcs:
        unit = next((u for a, b, u in units if a <= addr < b), None)
        state = "decompiled" if unit else "library" if addr in sdk else "remaining"
        out.append({"addr": addr, "size": max(size, 2), "name": name, "mode": mode, "state": state, "file": unit or ""})
    return out


def layout(funcs):
    """Packs blocks left to right in rows of WIDTH pixels; a block wider than the rest of a row continues below."""
    total = sum(f["size"] for f in funcs)
    rows = 72
    scale = WIDTH * rows / total
    x = y = 0.0
    for f in funcs:
        f["rects"] = []
        w = f["size"] * scale
        while w > 0:
            take = min(w, WIDTH - x)
            f["rects"].append((x, y, take))
            x += take
            w -= take
            if x >= WIDTH - 1e-6:
                x, y = 0.0, y + ROW_H + GAP
    height = y + (ROW_H if x else -GAP)
    return height


def stats(funcs):
    s = {}
    for state in COLORS:
        sel = [f for f in funcs if f["state"] == state]
        s[state] = {"functions": len(sel), "bytes": sum(f["size"] for f in sel)}
    game = [f for f in funcs if f["state"] != "library"]
    s["game"] = {"functions": len(game), "bytes": sum(f["size"] for f in game)}
    s["total"] = {"functions": len(funcs), "bytes": sum(f["size"] for f in funcs)}
    return s


def svg(funcs, height, s, interactive):
    top = 54
    parts = [f'<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 {WIDTH} {height + top + 4:.0f}" width="{WIDTH}" '
             f'font-family="-apple-system,Segoe UI,Helvetica,Arial,sans-serif">',
             f'<rect width="100%" height="100%" fill="#0d1117" rx="6"/>']
    dec, game = s["decompiled"], s["game"]
    pct_f = 100 * dec["functions"] / game["functions"]
    pct_b = 100 * dec["bytes"] / game["bytes"]
    parts.append(f'<text x="12" y="24" fill="#e6edf3" font-size="17" font-weight="600">Four Swords Anniversary Edition '
                 f'(EUR) ARM9: {dec["functions"]} / {game["functions"]} game functions decompiled '
                 f'({pct_f:.1f}%, {pct_b:.1f}% of code)</text>')
    lx = 12
    for state, color in COLORS.items():
        parts.append(f'<rect x="{lx}" y="34" width="12" height="12" fill="{color}" rx="2"/>'
                     f'<text x="{lx + 17}" y="44" fill="#8b949e" font-size="12">{LABELS[state]}</text>')
        lx += 190
    parts.append(f'<g transform="translate(0,{top})">')
    if interactive:
        for i, f in enumerate(funcs):
            for x, y, w in f["rects"]:
                parts.append(f'<rect data-i="{i}" x="{x:.2f}" y="{y:.0f}" width="{max(w, 0.6):.2f}" height="{ROW_H}" '
                             f'fill="{COLORS[f["state"]]}"/>')
    else:  # merge runs of the same state to keep the README image small
        run = None
        for f in funcs:
            for x, y, w in f["rects"]:
                if run and run[3] == f["state"] and abs(run[0] + run[2] - x) < 1e-6 and run[1] == y:
                    run[2] += w
                else:
                    if run:
                        parts.append(f'<rect x="{run[0]:.2f}" y="{run[1]:.0f}" width="{run[2]:.2f}" height="{ROW_H}" '
                                     f'fill="{COLORS[run[3]]}"/>')
                    run = [x, y, w, f["state"]]
        if run:
            parts.append(f'<rect x="{run[0]:.2f}" y="{run[1]:.0f}" width="{run[2]:.2f}" height="{ROW_H}" '
                         f'fill="{COLORS[run[3]]}"/>')
    parts.append("</g></svg>")
    return "\n".join(parts)


PAGE = """<!doctype html>
<html lang="en"><head><meta charset="utf-8"><meta name="viewport" content="width=device-width,initial-scale=1">
<title>FSAE progress map</title>
<style>
body{margin:0;background:#0d1117;color:#e6edf3;font:14px -apple-system,Segoe UI,Helvetica,Arial,sans-serif}
main{max-width:1000px;margin:0 auto;padding:16px}
svg{width:100%;height:auto;display:block}
rect[data-i]:hover{stroke:#fff;stroke-width:1}
rect.dim{opacity:.18}
#tip{position:fixed;pointer-events:none;background:#161b22;border:1px solid #30363d;border-radius:6px;padding:6px 9px;
font:12px ui-monospace,Consolas,monospace;display:none;white-space:pre}
input{background:#161b22;color:#e6edf3;border:1px solid #30363d;border-radius:6px;padding:6px 9px;width:min(320px,100%)}
p{color:#8b949e}a{color:#58a6ff}
</style></head><body><main>
<p>Every ARM9 function of the EUR ROM, in address order, sized by code size. Hover a block for details.
Source: <a href="https://github.com/0jasonn/fsae">0jasonn/fsae</a>.</p>
<p><input id="q" placeholder="Search function or file name"> <span id="hits"></span></p>
__SVG__
<div id="tip"></div>
<script>
const F=__DATA__;
const tip=document.getElementById('tip');
document.querySelectorAll('rect[data-i]').forEach(r=>{
 r.addEventListener('mousemove',e=>{const f=F[r.dataset.i];
  tip.textContent=f.name+'\\n0x'+f.addr.toString(16).padStart(8,'0')+'  '+f.size+' bytes  '+f.mode+'\\n'+
   ({decompiled:'decompiled in '+f.file,library:'TwlSDK / runtime',remaining:'not decompiled yet'})[f.state];
  tip.style.display='block';tip.style.left=Math.min(e.clientX+12,innerWidth-280)+'px';tip.style.top=(e.clientY+12)+'px';});
 r.addEventListener('mouseleave',()=>tip.style.display='none');});
document.getElementById('q').addEventListener('input',e=>{const q=e.target.value.toLowerCase();let n=0;
 document.querySelectorAll('rect[data-i]').forEach(r=>{const f=F[r.dataset.i];
  const hit=!q||f.name.toLowerCase().includes(q)||f.file.toLowerCase().includes(q);r.classList.toggle('dim',!hit);if(hit&&q)n++;});
 document.getElementById('hits').textContent=q?n+' blocks':'';});
</script></main></body></html>
"""


def main():
    funcs = load()
    height = layout(funcs)
    s = stats(funcs)
    DOCS.mkdir(exist_ok=True)
    (DOCS / "progress.svg").write_text(svg(funcs, height, s, False), encoding="utf-8", newline="\n")
    data = [{k: f[k] for k in ("addr", "size", "name", "mode", "state", "file")} for f in funcs]
    page = PAGE.replace("__SVG__", svg(funcs, height, s, True)).replace("__DATA__", json.dumps(data, separators=(",", ":")))
    (DOCS / "progress.html").write_text(page, encoding="utf-8", newline="\n")
    (DOCS / "progress.json").write_text(json.dumps(s, indent=1) + "\n", encoding="utf-8", newline="\n")
    d, g = s["decompiled"], s["game"]
    print(f"{d['functions']}/{g['functions']} game functions, {100 * d['bytes'] / g['bytes']:.1f}% of game code")


if __name__ == "__main__":
    main()
