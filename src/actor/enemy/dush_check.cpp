#include "engine/functions.h"
#include "global.h"
#include "actor/enemy/dush_check.h"

// Functions in this file: dushCheck (0x0203ee28).

int dushCheck(Entity *e) {
    u16 cell;
    s32 dy;
    s32 dx;
    const s8 *hitbox;

    hitbox = (const s8 *)e->hitbox;
    dy = (e->y.HALF.HI + hitbox[1]) - mapState.originY;
    dx = e->x.HALF.HI - mapState.originX;
    cell = (u16)(((const s16 *)cellDeltaTable)[e->direction >> 3] * 3) + (u16)((dx >> 4) | ((dy >> 4) << 6));
    if (func_02084f2c(cell, e->layer, 9) == 0) {
        if (func_02083d4c(cell, e->layer) != 0) {
            return 1;
        }
    }
    return 0;
}
