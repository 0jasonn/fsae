#include "engine/functions.h"
#include "global.h"
#include "actor/object/setcommon.h"
#include "actor/object/set18.h"

// Waits for the BG cell under the entity to show tile 0x10e, then sets its type bits in the area mask. Starts the
// timer, or removes the entity when the timer is 0.
void set18_wait(Entity *e) {
    int bg;
    u16 cellValue;
    u16 tile;

    bg = GetBgBuffAdrs(e->layer);
    cellValue = *VARS(Vars_Set18, e)->cellPtr;
    tile = *(u16 *)(bg + cellValue * 2 + 0x5004);
    if (tile != 0x10e) {
        return;
    }
    em12_typeMasks[e->areaIndex] |= flagBits[e->type];
    if (e->timer != 0) {
        e->action++;
        VARS(Vars_Set18, e)->frameTimer = e->timer * 30;
    } else {
        PutObjWork(e);
    }
}

// Set18 actor, second unit (module set18). Address -> name:
//   0x02065764 set18_move

// Removes the entity once its type bits are all set in the area mask. Otherwise counts down the frame timer, then
// clears the cell (RewCell 0x10d) and clears the type bits from the area mask.
void set18_move(Entity *e) {
    int cell;
    int dy;
    int dx;

    if (e->subtimer != 0) {
        if (VARS(Vars_Set18, e)->typeBits == (VARS(Vars_Set18, e)->typeBits & em12_typeMasks[e->areaIndex])) {
            PutObjWork(e);
            return;
        }
    }
    if (--VARS(Vars_Set18, e)->frameTimer != 0) {
        return;
    }
    dy = e->y.HALF.HI - mapState.unk_1a;
    dx = e->x.HALF.HI - mapState.unk_18;
    cell = (dx >> 4) | ((dy >> 4) << 6);
    RewCell(0x10d, (u16)cell, e->layer);
    em12_typeMasks[e->areaIndex] &= ~flagBits[e->type];
    e->action--;
}
