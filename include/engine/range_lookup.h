#ifndef WIP_A_RANGE_LOOKUP_H
#define WIP_A_RANGE_LOOKUP_H

#include "types.h"

// Entry of a sorted range table (same layout as RangeEntry in src/engine/range_table.cpp).
typedef struct RangeEntry {
    u32 start;
    u32 lenFlags;      // bit 0 is a flag: the data follows the entry when set, otherwise it is at unk_08
    u8 *unk_08;
} RangeEntry;

// Lookup record filled by RangeLookup_Resolve. The caller presets table and tableEnd.
typedef struct RangeLookup {
    u32 base;          // 0x00: start of the matched range
    u8 *data;          // 0x04: packed data of the matched range, NULL when none
    u8 *item;          // 0x08: the packed item that holds the key, NULL when none
    void *table;       // 0x0c: first entry of the range table
    void *tableEnd;    // 0x10: end of the range table
    u32 unk_14;        // 0x14: not written by the lookup
} RangeLookup;

extern "C" {
void RangeLookup_Resolve(u32 key, RangeLookup *out);
s32 func_0200ca38(RangeLookup *out, u32 key);
void *RangeTable_Find(void *table, s32 count, u32 key);
const u8 *Packed_ReadOptional(const u8 *src);
}

#endif
