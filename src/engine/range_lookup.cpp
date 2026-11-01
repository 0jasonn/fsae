#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/range_lookup.h"

// RangeLookup_Resolve(key, out) (0x0200b334): finds the range that contains key in the table preset in out, then walks
// the packed (length, extra, value) items of its data until the one that holds key. out->item is set when found.
void RangeLookup_Resolve(u32 key, RangeLookup *out) {
    const u8 *p;
    RangeEntry *entry;
    s32 count;
    u32 offset;
    u32 acc;
    u32 span;
    u32 length;
    u32 extra;
    u32 value;

    out->data = NULL;
    out->item = NULL;
    if (func_0200ca38(out, key) == 0) {
        return;
    }
    count = ((u8 *)out->tableEnd - (u8 *)out->table) / 12;
    entry = (RangeEntry *)RangeTable_Find(out->table, count, key);
    if (entry == NULL) {
        return;
    }
    if (entry->lenFlags & 1) {
        out->data = (u8 *)entry + 8;
    } else {
        out->data = entry->unk_08;
    }
    out->base = entry->start;
    offset = key - entry->start;

    p = Packed_ReadOptional(out->data);
    acc = 0;
    for (;;) {
        p = func_0200b24c(p, &length);
        if (length == 0) {
            return;
        }
        p = func_0200b24c(p, &extra);
        p = func_0200b24c(p, &value);
        span = acc + length;
        if (offset < span) {
            return;
        }
        acc = span + extra;
        if (offset <= acc) {
            break;
        }
    }
    out->item = out->data + value;
}
