#include "engine/functions.h"
#include "knife/message/tilebuf.h"
#include "ui/widget/tile_record.h"

// TileBuffer_blitMap (0x020b771c): copies the present tiles of a tile map source into the tile buffer at pos. The
// source size gives the rectangle, which is clipped to the buffer bounds (self+8); tiles without bit 15 are skipped.
void TileBuffer_blitMap(void *self, s16 *pos, void **src) {
    s16 clip[4];
    s16 posCopy[2];
    s16 sizeCopy[2];
    s16 cell[2];
    TileMapWork map;
    u16 tile;
    TileMapWork *mapPtr;
    s16 row;
    TileRecord *rec;
    u16 *rowData;
    s16 col;

    rec = *(TileRecord **)*src;
    u16 width = rec->width;
    u16 height = rec->height;
    sizeCopy[0] = width;
    sizeCopy[1] = height;
    posCopy[0] = pos[0];
    posCopy[1] = pos[1];
    func_020b7488(clip, posCopy, sizeCopy, (u8 *)self + 8);
    if ((s16)(clip[2] - clip[0]) == 0) {
        return;
    }
    map.vtbl = &data_02126c18;
    map.unk_04 = 0;
    map.unk_08 = 0;
    map.unk_0c = 0;
    map.unk_0e = 0;
    map.unk_10 = 0;
    map.unk_14 = 0;
    mapPtr = (TileMapWork *)TileMap_setupFromSrc(&map, src);
    for (row = clip[1]; row < clip[3]; row++) {
        rowData = TileBuffer_getRow(self, (s16)(pos[1] + row));
        for (col = clip[0]; col < clip[2]; col++) {
            cell[0] = col;
            cell[1] = row;
            tile = ((TileMapObj *)mapPtr)->getCell(cell);
            if (tile & 0x8000) {
                rowData[pos[0] + col] = tile;
            }
        }
    }
}
