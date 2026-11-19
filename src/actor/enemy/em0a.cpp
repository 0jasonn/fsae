#include "engine/functions.h"
#include "global.h"
#include "actor/enemy/em13.h"
#include "actor/enemy/em0a.h"

// Functions in this file (actor em0a, original name from the debug build):
//   em0a_gatagata (0x0202bee8)

// em0a_gatagata: while the object has no child it searches for one in an area that grows by 0x10 every 4 frames.
// The timer bobs the y position through a 4-step table; when it runs out the action advances, the cell under the
// object is rewritten (by type) and a new set object is made at its position.
void em0a_gatagata(Entity *e) {
    if (e->child == NULL) {
        if ((e->timer & 3) == 0) {
            e->subtimer += 0x10;
        }
        Entity *found = FindTargetInRange(e, e->subtimer, e->subtimer);
        if (found != NULL) {
            e->child = found;
        }
    }
    e->timer--;
    e->y.HALF.HI += em0aBobOffsets[e->timer & 3];
    if (e->timer != 0) {
        return;
    }
    e->action += 1;
    e->zVelocity = 0x20000;
    u16 cell;
    switch (e->type) {
    case 0:
        if ((e->layer >> 14) != 2) {
            cell = (u16)(((e->x.HALF.HI - mapState.originX) >> 4) | (((e->y.HALF.HI - mapState.originY) >> 4) << 6));
            RewCell(0x2f, cell, e->layer);
        } else {
            cell = (u16)(((e->x.HALF.HI - mapState.originX) >> 4) | (((e->y.HALF.HI - mapState.originY) >> 4) << 6));
            RewCell(0x58, cell, e->layer);
        }
        break;
    case 1:
        cell = (u16)(((e->x.HALF.HI - mapState.originX) >> 4) | (((e->y.HALF.HI - mapState.originY) >> 4) << 6));
        RewCell(0x158, cell, e->layer);
        break;
    default:
        break;
    }
    {
        s32 slot = 0xf;
        Entity *obj = GetSetWork(slot, 4, 0x40);
        if (obj == NULL) {
            return;
        }
        ObjPosCopy(e, obj);
        func_02085f98(e, 0x230 - slot);
    }
}
