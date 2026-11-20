#!/usr/bin/env python3
"""Parallel statement-order permuter (from implementer C3's scratch/agentC3/pperm.py, which closed em03_damage,
em03_kuttsuki and finale_init when hand-picked orders didn't).

usage: python tools/pperm.py FILE A B [--max N] [--out DIR] [--threads T]

Permutes source lines A..B of FILE (0-based, inclusive). A line whose text starts with '    +' is glued to the line
before it (so a multi-line statement moves as one unit; the '+' is removed). Every order is compiled with
tools/trymatch.py -d; the number of differing lines is the score (lower is better). The best variant so far is written to
DIR/pp_best.cpp; on an exact match it prints MATCH and stops. With more than N orders (default 50000), a fixed random
sample of N is tried. Uses threads (each one runs its own compiler process), so it works from any shell; still run it in
the foreground and stop it before you report.
"""
import argparse, itertools, os, random, subprocess, sys
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent

ap = argparse.ArgumentParser()
ap.add_argument('file'); ap.add_argument('a', type=int); ap.add_argument('b', type=int)
ap.add_argument('--max', type=int, default=50000)
ap.add_argument('--out', default=None, help='work folder (default: <file dir>/pperm_work)')
ap.add_argument('--threads', type=int, default=8)
args = ap.parse_args()

src = Path(args.file).read_text().split('\n')
items = []
for line in src[args.a:args.b + 1]:
    if line.startswith('    +') and items:
        items[-1].append('    ' + line[5:].lstrip())
    else:
        items.append([line])
perms = list(itertools.permutations(range(len(items)))) if len(items) <= 9 else None
if perms is None or len(perms) > args.max:
    random.seed(7)
    if perms is None:
        seen = set(); perms = []
        while len(perms) < args.max:
            p = tuple(random.sample(range(len(items)), len(items)))
            if p not in seen: seen.add(p); perms.append(p)
    else:
        random.shuffle(perms); perms = perms[:args.max]
out = Path(args.out) if args.out else Path(args.file).resolve().parent / 'pperm_work'
out.mkdir(parents=True, exist_ok=True)

def run(job):
    n, perm = job
    body = [l for i in perm for l in items[i]]
    text = '\n'.join(src[:args.a] + body + src[args.b + 1:])
    p = out / ('pp_%d.cpp' % n)
    p.write_text(text)
    try:
        res = subprocess.run([sys.executable, str(ROOT / 'tools/trymatch.py'), str(p), '-d'], capture_output=True,
                             text=True, timeout=120, cwd=ROOT).stdout
    except subprocess.TimeoutExpired:
        res = ''
    finally:
        p.unlink(missing_ok=True)
    lines = res.splitlines()
    if not lines or 'match' not in lines[0]:
        return None, perm, text, False  # did not compile: never counts as a candidate
    ok = lines[0].startswith('dsi/1.2: 1 match') and ' 0 differ' in lines[0]
    score = sum('>>' in x or 'call at' in x for x in lines)
    return score, perm, text, ok

best = None
with ThreadPoolExecutor(args.threads) as ex:
    for score, perm, text, ok in ex.map(run, list(enumerate(perms))):
        if score is None:
            continue
        if best is None or score < best[0]:
            best = (score, perm); print(best, flush=True)
            (out / 'pp_best.cpp').write_text(text)
        if ok:
            print('MATCH'); break
print('done', len(perms), 'orders; best', best)
