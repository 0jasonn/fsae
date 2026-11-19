#include "engine/functions.h"
#include "global.h"
#include "actor/object/pot.h"

// pot_push (0x0205f0f4): a pushed pot slides until its timer runs out. At the end, unless the cell is held, the pot
// settles: it remembers the BG cell and state byte under it (pots hitting a 0x4002 cell break at once) and marks the
// cell as occupied (0x4002, state 0x1d).
void pot_push(Entity *e) {
    u8 *bg;
    if (e->timer-- != 0) {
        MoveDir(e);
        func_0208aea0(e);
        return;
    }
    if (func_02085ccc(e) != 0) {
        return;
    }
    e->action = 1;
    bg = (u8 *)GetBgBuffAdrs(e->layer);
    VARS(Vars_Pot, e)->savedCell = *(u16 *)(bg + MAP_CELL_INDEX(e->x.HALF.HI, e->y.HALF.HI) * 2 + 4);
    if (VARS(Vars_Pot, e)->savedCell == 0x4002) {
        pot_clash(e, NULL);
        return;
    }
    VARS(Vars_Pot, e)->savedCellState = *(bg + MAP_CELL_INDEX(e->x.HALF.HI, e->y.HALF.HI) + 0x2004);
    *(u16 *)(bg + MAP_CELL_INDEX(e->x.HALF.HI, e->y.HALF.HI) * 2 + 4) = 0x4002;
    *(bg + MAP_CELL_INDEX(e->x.HALF.HI, e->y.HALF.HI) + 0x2004) = 0x1d;
    func_02089524(e);
}
