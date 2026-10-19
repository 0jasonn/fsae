#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "game/cellcommon.h"

// Functions in this file (original names from the debug build):
//   frame_block_set

// Two offset tables (u16 at 4-byte stride, indexed by the block kind)
extern u8 data_0213492c[];
extern u8 em12_spawnOffsetY[];

// Sets the cell of one frame block: tile offsets come from the kind table, the cell is converted to 64-cell rows
ARM void frame_block_set(u16 x, u16 y, u16 cell, u8 kind) {
    u16 tileX;
    u16 tileY;

    tileX = y + *(u16 *)(em12_spawnOffsetY + kind * 4); tileY = x + *(u16 *)(data_0213492c + kind * 4);
    RewCellOne(0x136, (tileY >> 4) | (tileX >> 4 << 6), cell);
}
