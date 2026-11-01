#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "ui/widget/pane.h"
#include "ui/widget/tile_row_api.h"
#include "ui/widget/tile_record.h"

// tile_row: function TileBuffer_getRow (0x020b7508), matching. The buffer is read with the fields +0x10 (base),
// +0x14 (row width) and +0x16 (row count, a power of two).

// TileBuffer_getRow(self, index) (0x020b7508, provisional name): pointer to the entry at index, the index wraps at
// the row count
u16 *TileBuffer_getRow(void *self, u32 index) {
    s16 rowCount;
    s16 rowWidth;
    u16 *base;

    base = *(u16 **)((u8 *)self + 0x10);
    rowWidth = *(s16 *)((u8 *)self + 0x14);
    rowCount = *(s16 *)((u8 *)self + 0x16);
    return base + rowWidth * (index & (rowCount - 1));
}

// tile_row_2: function TileMap_setupFromSrc (0x020b7528), matching. It follows TileBuffer_getRow. The kind byte of the
// source record selects TileMap_initWithOffset (kind 4) or func_020b7578 (kind 7, parked, the other tile map setup).

extern "C" void TileMap_initWithOffset(TileMap *self, void **src);

// TileMap_setupFromSrc(self, src) (0x020b7528, provisional name): sets up self from the record that src points to
// through its pointer. Returns self.
void *TileMap_setupFromSrc(void *self, void **src) {
    TileRecord *rec;

    rec = *(TileRecord **)*src;
    if (rec->kind != 4) {
        if (rec->kind == 7 && self != NULL) {
            func_020b7578(self, src);
        }
    } else {
        if (self != NULL) {
            TileMap_initWithOffset((TileMap *)self, src);
        }
    }
    return self;
}
