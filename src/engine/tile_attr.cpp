#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/pane.h"

// tile_attr: function TileMap_getCellAttr (0x020b766c), matching. The map record is the one of tile_map.cpp: base at +4,
// the cell flags table at +8, the row stride at +0x10 and a flag byte at +0x14.

// TileMap_getCellAttr(self, pos) (0x020b766c, provisional name): the cell at pos (one byte) indexes the flags table; the
// result has bit 0x8000 set unless the cell is 0 and the flag byte is set (then it is cleared)
extern "C" u16 TileMap_getCellAttr(void *self, const s16 *pos);
ARM u16 TileMap_getCellAttr(void *self, const s16 *pos) {
    u8 *row;
    u32 cell;
    u32 bits;
    u16 *table;

    row = *(u8 **)((u8 *)self + 0x4) + pos[1] * *(u32 *)((u8 *)self + 0x10);
    cell = row[pos[0]];
    bits = 0x8000;
    if (cell == 0) {
        if (*(u8 *)((u8 *)self + 0x14) != 0) {
            bits = 0;
        }
    }
    table = *(u16 **)((u8 *)self + 0x8);
    return (u16)(bits | table[cell]);
}
