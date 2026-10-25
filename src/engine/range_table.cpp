#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Entry of a sorted range table: start, length (bit 0 is a flag) and one more word.
typedef struct RangeEntry {
    u32 start;
    u32 lenFlags;
    u32 unk_08;
} RangeEntry;

extern "C" void *RangeTable_Find(RangeEntry *table, s32 count, u32 key);

// RangeTable_Find(table, count, key) (0x0200b2d0): binary search for the entry whose range [start, start + length)
// contains key. Returns that entry, or NULL when no range contains key.
ARM void *RangeTable_Find(RangeEntry *table, s32 count, u32 key) {
    s32 lo;
    s32 hi;
    s32 mid;
    RangeEntry *entry;

    lo = 0;
    hi = count - 1;
    while (lo <= hi) {
        mid = (lo + hi) >> 1;
        entry = &table[mid];
        if (key < entry->start) {
            hi = mid - 1;
        } else if (key > entry->start + (entry->lenFlags & ~1)) {
            lo = mid + 1;
        } else {
            return entry;
        }
    }
    return NULL;
}
