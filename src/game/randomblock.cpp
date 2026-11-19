#include "engine/functions.h"
#include "game/randomblock.h"
#include "global.h"

// RandomBlockSet (0x0204e690): walks a list of byte pairs (column, row | 0x80 flag), ended by a 0xff column, and sets a
// frame block for each: the position is the cell centre ((n << 4) | 8), the cell value is 0x8000 when bit 7 of the
// row byte is set, else 0x4000.
void RandomBlockSet(const u8 *list, u8 param) {
    const u8 *entry = list;
    u8 column = *entry;
    u8 flag;
    u16 x;
    u16 y;
    u16 cell;
    if (column == 0xff) {
        return;
    }
    do {
        flag = entry[1];
        x = (column << 4) | 8;
        y = ((flag << 4) | 8) & 0x3ff;
        cell = (flag & 0x80) ? 0x8000 : 0x4000;
        frame_block_set(x, y, cell, param);
        column = *(entry += 2);
    } while (column != 0xff);
}
