#include "engine/functions.h"
#include "global.h"

extern "C" void *ResChunk_Find(u8 *base, u32 magic);
extern "C" void func_020c2ea8(u8 *body);

// ResChunk_OpenKBEC (ResChunk_OpenKBEC, provisional name): as ResChunk_OpenKNBA for the KBEC chunk, with func_020c2ea8 as the
// setup of the body.
extern "C" s32 ResChunk_OpenKBEC(u8 *base, u8 **out);
ARM s32 ResChunk_OpenKBEC(u8 *base, u8 **out) {
    u8 *chunk;

    chunk = (u8 *)ResChunk_Find(base, 0x4345424b);
    if (chunk == 0) {
        *out = 0;
        return 0;
    }
    func_020c2ea8(chunk + 8);
    *out = chunk + 8;
    return 1;
}

// ResTable_GetEntryAt (ResTable_GetEntryAt, provisional name): the entry at index, or 0 when index is not below the count at +0.
// Entries are 0x10 bytes when bit 0 of the flags at +2 is set, 8 bytes otherwise.
extern "C" u8 *ResTable_GetEntryAt(u8 *table, u32 index);
ARM u8 *ResTable_GetEntryAt(u8 *table, u32 index) {
    u16 flags;
    u8 *base;

    if (index >= *(u16 *)table) {
        return 0;
    }
    flags = *(u16 *)(table + 2);
    base = *(u8 **)(table + 4);
    if (flags & 1) {
        return base + (index << 4);
    }
    return base + (index << 3);
}
