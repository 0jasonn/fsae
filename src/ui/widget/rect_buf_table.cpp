#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "ui/widget/rect_links.h"

// rect_buf_table: function RectBufTable_setup (0x020bc2d0), provisional name.

// Table entry returned by Table_getEntry58: the limit at +0x30
typedef struct RectBufTableEntry {
    u8 unk_00[0x30];   // 0x00
    s32 limit;         // 0x30
} RectBufTableEntry;

// Record of the set: the blocks at +0x18 and +0x34 are both 0x2c00 bytes long, so the ones used here are at +0x2c18
// (capacity block) and +0x2c34 (data block)
typedef struct RectBufTable {
    u8 unk_00[0x18];
    u8 unk_18[0x2c00];
    u8 unk_2c18[0x1c];
    u8 unk_2c34[0x400];
} RectBufTable;

extern "C" void *Table_getEntry58(u8 *self, s32 index);
extern "C" s32 func_020c40a4(void *dst, s32 size, s32 limit, s32 zero, s32 *pair, s32 zero2, s32 zero3);
extern "C" s32 Cursor_GetSpan(void *dst);
extern "C" void OamRing_Push(void *dst, void *src, s32 count);

// RectBufTable_setup(self, index, arg2, arg3) (0x020bc2d0, provisional name): looks up the table entry for index, and if
// it has a limit fills the pair (arg2, arg3) with func_020c40a4 into the second block, then copies count bytes from
// the second block to the first when count is below the capacity Cursor_GetSpan returns. Returns TRUE when it copied
extern "C" BOOL RectBufTable_setup(RectBufTable *self, s32 index, s32 arg2, s32 arg3);
BOOL RectBufTable_setup(RectBufTable *self, s32 index, s32 arg2, s32 arg3) {
    RectBufTableEntry *entry;
    s32 pair[2];
    u32 count;
    u32 capacity;
    s32 limit;

    entry = (RectBufTableEntry *)Table_getEntry58((u8 *)self, index);
    if (entry != NULL && entry->limit != 0) {
        limit = entry->limit;
        pair[0] = arg2;
        pair[1] = arg3;
        count = func_020c40a4(self->unk_2c34, 0x80, limit, 0, pair, 0, 0);
        capacity = Cursor_GetSpan(self->unk_2c18);
        if (count < capacity) {
            OamRing_Push(self->unk_2c18, self->unk_2c34, count);
            return TRUE;
        }
    }
    return FALSE;
}
