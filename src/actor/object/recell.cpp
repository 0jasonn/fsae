#include "actor/object/recell.h"

// Rewrites the map cells around a block (recell0/recell1, 0x02066910 and 0x02067040): the cell list for the block type
// is applied around the cell under the block position; cases 0 and 2 start 8 pixels to the left.
void recell0(Entity *e) {
    const u16 *cells;
    int cell;

    cells = recell0Cells[e->type];
    switch (e->type) {
    case 0:
        cell = (u16)(((e->x.HALF.HI - 8 - mapState.scrollX) >> 4) | (((e->y.HALF.HI - mapState.scrollY) >> 4) << 6));
        RewCell(cells[0], cell - 65, e->layer);
        RewCell(cells[1], cell - 64, e->layer);
        RewCell(cells[2], cell - 63, e->layer);
        RewCell(cells[3], cell - 62, e->layer);
        RewCell(cells[4], cell - 1, e->layer);
        RewCell(cells[5], cell, e->layer);
        RewCell(cells[6], cell + 1, e->layer);
        RewCell(cells[7], cell + 2, e->layer);
        RewCell(cells[8], cell + 63, e->layer);
        RewCell(cells[9], cell + 64, e->layer);
        RewCell(cells[10], cell + 65, e->layer);
        RewCell(cells[11], cell + 66, e->layer);
        break;
    case 1:
        cell = (u16)(((e->x.HALF.HI - mapState.scrollX) >> 4) | (((e->y.HALF.HI - mapState.scrollY) >> 4) << 6));
        RewCell(cells[0], cell - 66, e->layer);
        RewCell(cells[1], cell - 65, e->layer);
        RewCell(cells[2], cell - 64, e->layer);
        RewCell(cells[3], cell - 63, e->layer);
        RewCell(cells[4], cell - 62, e->layer);
        RewCell(cells[5], cell - 2, e->layer);
        RewCell(cells[6], cell - 1, e->layer);
        RewCell(cells[7], cell, e->layer);
        RewCell(cells[8], cell + 1, e->layer);
        RewCell(cells[9], cell + 2, e->layer);
        RewCell(cells[10], cell + 62, e->layer);
        RewCell(cells[11], cell + 63, e->layer);
        RewCell(cells[12], cell + 64, e->layer);
        RewCell(cells[13], cell + 65, e->layer);
        RewCell(cells[14], cell + 66, e->layer);
        break;
    case 2:
        cell = (u16)(((e->x.HALF.HI - 8 - mapState.scrollX) >> 4) | (((e->y.HALF.HI - mapState.scrollY) >> 4) << 6));
        RewCell(cells[0], cell - 66, e->layer);
        RewCell(cells[1], cell - 65, e->layer);
        RewCell(cells[2], cell - 64, e->layer);
        RewCell(cells[3], cell - 63, e->layer);
        RewCell(cells[4], cell - 62, e->layer);
        RewCell(cells[5], cell - 61, e->layer);
        RewCell(cells[6], cell - 2, e->layer);
        RewCell(cells[7], cell - 1, e->layer);
        RewCell(cells[8], cell, e->layer);
        RewCell(cells[9], cell + 1, e->layer);
        RewCell(cells[10], cell + 2, e->layer);
        RewCell(cells[11], cell + 3, e->layer);
        RewCell(cells[12], cell + 62, e->layer);
        RewCell(cells[13], cell + 63, e->layer);
        RewCell(cells[14], cell + 64, e->layer);
        RewCell(cells[15], cell + 65, e->layer);
        RewCell(cells[16], cell + 66, e->layer);
        RewCell(cells[17], cell + 67, e->layer);
        break;
    case 3:
        cell = (u16)(((e->x.HALF.HI - mapState.scrollX) >> 4) | (((e->y.HALF.HI - mapState.scrollY) >> 4) << 6));
        RewCell(cells[0], cell - 67, e->layer);
        RewCell(cells[1], cell - 66, e->layer);
        RewCell(cells[2], cell - 65, e->layer);
        RewCell(cells[3], cell - 64, e->layer);
        RewCell(cells[4], cell - 63, e->layer);
        RewCell(cells[5], cell - 62, e->layer);
        RewCell(cells[6], cell - 61, e->layer);
        RewCell(cells[7], cell - 3, e->layer);
        RewCell(cells[8], cell - 2, e->layer);
        RewCell(cells[9], cell - 1, e->layer);
        RewCell(cells[10], cell, e->layer);
        RewCell(cells[11], cell + 1, e->layer);
        RewCell(cells[12], cell + 2, e->layer);
        RewCell(cells[13], cell + 3, e->layer);
        RewCell(cells[14], cell + 61, e->layer);
        RewCell(cells[15], cell + 62, e->layer);
        RewCell(cells[16], cell + 63, e->layer);
        RewCell(cells[17], cell + 64, e->layer);
        RewCell(cells[18], cell + 65, e->layer);
        RewCell(cells[19], cell + 66, e->layer);
        RewCell(cells[20], cell + 67, e->layer);
        break;
    }
}

void recell1(Entity *e) {
    const u16 *cells;
    int cell;

    cells = recell1Cells[e->type];
    switch (e->type) {
    case 0:
        cell = (u16)(((e->x.HALF.HI - 8 - mapState.scrollX) >> 4) | (((e->y.HALF.HI - mapState.scrollY) >> 4) << 6));
        RewCell(cells[0], cell - 65, e->layer);
        RewCell(cells[1], cell - 64, e->layer);
        RewCell(cells[2], cell - 63, e->layer);
        RewCell(cells[3], cell - 62, e->layer);
        RewCell(cells[4], cell - 1, e->layer);
        RewCell(cells[5], cell, e->layer);
        RewCell(cells[6], cell + 1, e->layer);
        RewCell(cells[7], cell + 2, e->layer);
        RewCell(cells[8], cell + 63, e->layer);
        RewCell(cells[9], cell + 64, e->layer);
        RewCell(cells[10], cell + 65, e->layer);
        RewCell(cells[11], cell + 66, e->layer);
        break;
    case 1:
        cell = (u16)(((e->x.HALF.HI - mapState.scrollX) >> 4) | (((e->y.HALF.HI - mapState.scrollY) >> 4) << 6));
        RewCell(cells[0], cell - 66, e->layer);
        RewCell(cells[1], cell - 65, e->layer);
        RewCell(cells[2], cell - 64, e->layer);
        RewCell(cells[3], cell - 63, e->layer);
        RewCell(cells[4], cell - 62, e->layer);
        RewCell(cells[5], cell - 2, e->layer);
        RewCell(cells[6], cell - 1, e->layer);
        RewCell(cells[7], cell, e->layer);
        RewCell(cells[8], cell + 1, e->layer);
        RewCell(cells[9], cell + 2, e->layer);
        RewCell(cells[10], cell + 62, e->layer);
        RewCell(cells[11], cell + 63, e->layer);
        RewCell(cells[12], cell + 64, e->layer);
        RewCell(cells[13], cell + 65, e->layer);
        RewCell(cells[14], cell + 66, e->layer);
        break;
    case 2:
        cell = (u16)(((e->x.HALF.HI - 8 - mapState.scrollX) >> 4) | (((e->y.HALF.HI - mapState.scrollY) >> 4) << 6));
        RewCell(cells[0], cell - 66, e->layer);
        RewCell(cells[1], cell - 65, e->layer);
        RewCell(cells[2], cell - 64, e->layer);
        RewCell(cells[3], cell - 63, e->layer);
        RewCell(cells[4], cell - 62, e->layer);
        RewCell(cells[5], cell - 61, e->layer);
        RewCell(cells[6], cell - 2, e->layer);
        RewCell(cells[7], cell - 1, e->layer);
        RewCell(cells[8], cell, e->layer);
        RewCell(cells[9], cell + 1, e->layer);
        RewCell(cells[10], cell + 2, e->layer);
        RewCell(cells[11], cell + 3, e->layer);
        RewCell(cells[12], cell + 62, e->layer);
        RewCell(cells[13], cell + 63, e->layer);
        RewCell(cells[14], cell + 64, e->layer);
        RewCell(cells[15], cell + 65, e->layer);
        RewCell(cells[16], cell + 66, e->layer);
        RewCell(cells[17], cell + 67, e->layer);
        break;
    case 3:
        cell = (u16)(((e->x.HALF.HI - mapState.scrollX) >> 4) | (((e->y.HALF.HI - mapState.scrollY) >> 4) << 6));
        RewCell(cells[0], cell - 67, e->layer);
        RewCell(cells[1], cell - 66, e->layer);
        RewCell(cells[2], cell - 65, e->layer);
        RewCell(cells[3], cell - 64, e->layer);
        RewCell(cells[4], cell - 63, e->layer);
        RewCell(cells[5], cell - 62, e->layer);
        RewCell(cells[6], cell - 61, e->layer);
        RewCell(cells[7], cell - 3, e->layer);
        RewCell(cells[8], cell - 2, e->layer);
        RewCell(cells[9], cell - 1, e->layer);
        RewCell(cells[10], cell, e->layer);
        RewCell(cells[11], cell + 1, e->layer);
        RewCell(cells[12], cell + 2, e->layer);
        RewCell(cells[13], cell + 3, e->layer);
        RewCell(cells[14], cell + 61, e->layer);
        RewCell(cells[15], cell + 62, e->layer);
        RewCell(cells[16], cell + 63, e->layer);
        RewCell(cells[17], cell + 64, e->layer);
        RewCell(cells[18], cell + 65, e->layer);
        RewCell(cells[19], cell + 66, e->layer);
        RewCell(cells[20], cell + 67, e->layer);
        break;
    }
}
