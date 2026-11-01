#include "engine/functions.h"
#include "engine/tile_row_api.h"
#include "engine/tilebuf.h"

// TileBuffer_fillRect (0x020b73b8): clips the rectangle at pos (size from size) to the bounds of self (self+8)
// and writes value into every tile of the clipped area.
void TileBuffer_fillRect(void *self, s16 *pos, s16 *size, u16 value) {
    s16 clip[4];
    s16 posCopy[2];
    s16 sizeCopy[2];
    s32 row;
    s32 col;
    u16 *rowData;
    s16 width;

    sizeCopy[0] = size[0];
    sizeCopy[1] = size[1];
    posCopy[0] = pos[0];
    posCopy[1] = pos[1];
    func_020b7488(clip, posCopy, sizeCopy, (u8 *)self + 8);
    width = clip[2] - clip[0];
    if (width != 0) {
        for (row = clip[1]; row < clip[3]; row++) {
            rowData = TileBuffer_getRow(self, (s16)(pos[1] + row));
            for (col = clip[0]; col < clip[2]; col++) {
                rowData[pos[0] + col] = value;
            }
        }
    }
}
