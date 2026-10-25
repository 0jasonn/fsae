#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/pane.h"

// tile_row: function TileBuffer_getRow (0x020b7508), matching. The buffer is read with the fields +0x10 (base),
// +0x14 (row width) and +0x16 (row count, a power of two).

// TileBuffer_getRow(self, index) (0x020b7508, provisional name): pointer to the entry at index, the index wraps at
// the row count
extern "C" u16 *TileBuffer_getRow(void *self, u32 index);
ARM u16 *TileBuffer_getRow(void *self, u32 index) {
    s16 rowCount;
    s16 rowWidth;
    u16 *base;

    base = *(u16 **)((u8 *)self + 0x10);
    rowWidth = *(s16 *)((u8 *)self + 0x14);
    rowCount = *(s16 *)((u8 *)self + 0x16);
    return base + rowWidth * (index & (rowCount - 1));
}
