#include "engine/functions.h"
#include "global.h"
#include "object/cellcalls.h"

// rewDoor (original name, knife_rewDoor at 0x02071c8c): rewrites the six map cells around the door cell
// with the ids in table, using a layout chosen by e->type & 3. Cells are relative to the door cell.

extern "C" void knife_rewDoor(Entity *e, const u16 *table);

ARM void knife_rewDoor(Entity *e, const u16 *table) {
    s32 cell;

    cell = (u16)(((e->x.HALF.HI - data_0212c648.originX) >> 4) | (((e->y.HALF.HI - data_0212c648.originY) >> 4) << 6));
    switch (e->type & 3) {
    case 0:
        RewCell(table[0], (u16)(cell - 0x41), 0x8000);
        RewCell(table[1], (u16)(cell - 0x40), 0x8000);
        RewCell(table[2], (u16)(cell - 0x3f), 0x8000);
        RewCell(table[3], (u16)(cell - 1), 0x4000);
        RewCell(table[4], (u16)(cell), 0x4000);
        RewCell(table[5], (u16)(cell + 1), 0x4000);
        break;
    case 1:
        RewCell(table[0], (u16)(cell - 0x40), 0x4000);
        RewCell(table[1], (u16)(cell - 0x3f), 0x8000);
        RewCell(table[2], (u16)(cell), 0x4000);
        RewCell(table[3], (u16)(cell + 1), 0x8000);
        RewCell(table[4], (u16)(cell + 0x40), 0x4000);
        RewCell(table[5], (u16)(cell + 0x41), 0x8000);
        break;
    case 2:
        RewCell(table[0], (u16)(cell - 1), 0x4000);
        RewCell(table[1], (u16)(cell), 0x4000);
        RewCell(table[2], (u16)(cell + 1), 0x4000);
        RewCell(table[3], (u16)(cell + 0x3f), 0x8000);
        RewCell(table[4], (u16)(cell + 0x40), 0x8000);
        RewCell(table[5], (u16)(cell + 0x41), 0x8000);
        break;
    case 3:
        RewCell(table[0], (u16)(cell - 0x41), 0x8000);
        RewCell(table[1], (u16)(cell - 0x40), 0x4000);
        RewCell(table[2], (u16)(cell - 1), 0x8000);
        RewCell(table[3], (u16)(cell), 0x4000);
        RewCell(table[4], (u16)(cell + 0x3f), 0x8000);
        RewCell(table[5], (u16)(cell + 0x40), 0x4000);
        break;
    }
}
