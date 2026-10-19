#!/usr/bin/env python3
"""Recovers original function names from the KQ9J debug build and maps them onto the retail EUR ARM9.

The debug ARM9 is built with profiling hooks: every function starts with
`push {r0, lr}; ldr r0, =name; bl __PROFILE_ENTRY; pop {r0, lr}` and calls __PROFILE_EXIT before returning.
The hooks are stripped, the remaining code is normalised (branch targets and pc-relative loads masked) and
compared with every retail function.

Usage: python tools/debugsyms.py [--debug-bin scratch/debug/arm9_debug.bin] > config/eur/debug_names.tsv
"""
import argparse, collections, re, struct, sys
from pathlib import Path
import capstone

ROOT = Path(__file__).parent.parent
BASE = 0x02004000


def norm_arm(code, addr):
    """Instruction list up to the first literal pool, with addresses masked."""
    md = capstone.Cs(capstone.CS_ARCH_ARM, capstone.CS_MODE_ARM)
    md.detail = False
    out, pool = [], len(code)
    for off in range(0, len(code) - 3, 4):
        if off >= pool:
            break
        insns = list(md.disasm(code[off:off + 4], addr + off))
        if not insns:
            out.append("?")
            continue
        i = insns[0]
        m = re.search(r"\[pc, #(-?0x[0-9a-f]+|-?\d+)\]", i.op_str)
        if m and i.mnemonic.startswith("ldr"):
            tgt = off + 8 + int(m.group(1), 0)
            if off < tgt < pool:
                pool = tgt
            out.append(f"{i.mnemonic} {i.op_str.split(',')[0]}, =POOL")
        elif i.mnemonic in ("bl", "blx") or (i.mnemonic.startswith("b") and i.op_str.startswith("#")):
            if i.mnemonic in ("bl", "blx"):
                out.append(f"{i.mnemonic} CALL")
            else:
                out.append(f"{i.mnemonic} {int(i.op_str[1:], 0) - (addr + off):+d}")
        else:
            out.append(f"{i.mnemonic} {i.op_str}")
    return out


def strip_profile(ins):
    """Removes the entry and exit profiling hooks from a normalised debug function."""
    if ins[:4] == ["push {r0, lr}", "ldr r0, =POOL", "bl CALL", "pop {r0, lr}"]:
        ins = ins[4:]
    out, i = [], 0
    while i < len(ins):
        if ins[i:i + 5] == ["ldr lr, [sp, #4]", "sub sp, sp, #4", "stmdb sp!, {lr}", "bl CALL", "add sp, sp, #8"]:
            i += 5
            continue
        out.append(ins[i])
        i += 1
    return out


def rebase_branches(ins):
    """Branch offsets change when hooks are removed, so keep only the branch condition."""
    return tuple(re.sub(r"^(b\w*) [+-]\d+$", r"\1 REL", x) for x in ins)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--debug-bin", type=Path, default=ROOT / "scratch/debug/arm9_debug.bin")
    ap.add_argument("--retail-bin", type=Path, default=ROOT / "extract/eur/arm9/arm9.bin")
    ap.add_argument("--min-score", type=float, default=0.6)
    args = ap.parse_args()
    dbg = args.debug_bin.read_bytes()
    ret = args.retail_bin.read_bytes()

    # Name strings referenced from literal pools.
    names = {BASE + m.start(1): m.group(1).decode() for m in re.finditer(rb"(?<=\0)([A-Za-z_][A-Za-z0-9_]{2,})\0", dbg)}
    # Debug functions: profiling prologue whose ldr points at a name.
    PUSH = struct.pack("<I", 0xe92d4001)
    funcs = []
    for m in re.finditer(re.escape(PUSH), dbg):
        off = m.start()
        if off % 4:
            continue
        w = struct.unpack_from("<I", dbg, off + 4)[0]
        if w & 0xfffff000 != 0xe59f0000:
            continue
        name = names.get(struct.unpack_from("<I", dbg, off + 12 + (w & 0xfff))[0])
        if name:
            funcs.append((off, name))
    funcs.sort()
    print(f"debug functions with names: {len(funcs)}", file=sys.stderr)

    dsig = collections.defaultdict(list)
    for (off, name), nxt in zip(funcs, funcs[1:] + [(len(dbg), None)]):
        code = dbg[off:min(nxt[0], off + 0x4000)]
        dsig[rebase_branches(strip_profile(norm_arm(code, BASE + off)))].append((BASE + off, name))

    import json
    sdk = {json.loads(l)["address"] for l in (ROOT / "config/eur/sdk_matches.jsonl").read_text().splitlines() if l.strip()}
    retail = []
    for line in (ROOT / "config/eur/arm9/symbols.txt").read_text().splitlines():
        m = re.match(r"(\S+) kind:function\(arm,size=0x([0-9a-f]+)[^)]*\) addr:0x([0-9a-f]+)", line)
        if m and int(m.group(3), 16) not in sdk:
            retail.append((int(m.group(3), 16), int(m.group(2), 16), m.group(1)))
    dfuncs = []  # (addr, name, sig) in address order
    for sig, lst in dsig.items():
        for addr, name in lst:
            dfuncs.append((addr, name, sig))
    dfuncs.sort()
    rfuncs = [(addr, cur, rebase_branches(norm_arm(ret[addr - BASE:addr - BASE + size], addr))) for addr, size, cur in sorted(retail)]

    # Anchors: unique exact matches, kept in increasing order on both sides.
    dindex = {a: i for i, (a, _, _) in enumerate(dfuncs)}
    pairs = []
    for ri, (addr, cur, sig) in enumerate(rfuncs):
        cands = dsig.get(sig, [])
        if len(cands) == 1:
            pairs.append((ri, dindex[cands[0][0]]))
    pairs = longest_increasing(pairs)
    print(f"anchors: {len(pairs)}", file=sys.stderr)

    result = {ri: (di, 1.0) for ri, di in pairs}
    bounds = [(-1, -1)] + pairs + [(len(rfuncs), len(dfuncs))]
    for (r0, d0), (r1, d1) in zip(bounds, bounds[1:]):
        R, D = list(range(r0 + 1, r1)), list(range(d0 + 1, d1))
        if R and D and len(R) * len(D) <= 40000:
            for ri, di, score in align(R, D, rfuncs, dfuncs, args.min_score):
                result[ri] = (di, score)

    print("retail_addr	retail_name	debug_addr	original_name	score")
    for ri in sorted(result):
        di, score = result[ri]
        print(f"{rfuncs[ri][0]:#010x}	{rfuncs[ri][1]}	{dfuncs[di][0]:#010x}	{dfuncs[di][1]}	{score:.2f}")
    print(f"retail ARM functions: {len(rfuncs)}, named: {len(result)}", file=sys.stderr)


def longest_increasing(pairs):
    """Longest chain of pairs increasing in both members (pairs already sorted by the first)."""
    import bisect
    tails, tails_idx, prev = [], [], [None] * len(pairs)
    for i, (_, d) in enumerate(pairs):
        k = bisect.bisect_left(tails, d)
        if k == len(tails):
            tails.append(d); tails_idx.append(i)
        else:
            tails[k] = d; tails_idx[k] = i
        prev[i] = tails_idx[k - 1] if k else None
    out, i = [], tails_idx[-1] if tails_idx else None
    while i is not None:
        out.append(pairs[i]); i = prev[i]
    return out[::-1]


def similarity(a, b):
    import difflib
    if not a or not b or min(len(a), len(b)) / max(len(a), len(b)) < 0.5:
        return 0.0
    return difflib.SequenceMatcher(None, a, b, autojunk=False).ratio()


def align(R, D, rfuncs, dfuncs, min_score):
    """Order-preserving alignment of the functions between two anchors that maximises total similarity."""
    n, m = len(R), len(D)
    sim = [[similarity(rfuncs[r][2], dfuncs[d][2]) for d in D] for r in R]
    best = [[0.0] * (m + 1) for _ in range(n + 1)]
    for i in range(n - 1, -1, -1):
        for j in range(m - 1, -1, -1):
            take = sim[i][j] + best[i + 1][j + 1] if sim[i][j] >= min_score else -1
            best[i][j] = max(take, best[i + 1][j], best[i][j + 1])
    i = j = 0
    out = []
    while i < n and j < m:
        if sim[i][j] >= min_score and best[i][j] == sim[i][j] + best[i + 1][j + 1]:
            out.append((R[i], D[j], sim[i][j])); i += 1; j += 1
        elif best[i][j] == best[i + 1][j]:
            i += 1
        else:
            j += 1
    return out

if __name__ == "__main__":
    main()
