#include "engine/functions.h"
#include "global.h"
#include "actor/enemy/attset.h"

// Dash checks (em20 dash): dushInitCheck (0x0203ed84) walks the four cells ahead of the entity. Both use the grid origin mapState and the per-direction cell step table
// cellDeltaTable (0x020cf91c).

extern GridOrigin mapState;
extern const u8 cellDeltaTable[];

int func_02083d4c(u16 cell, u16 layer);                       // thumb helper, C++ linkage (_Z13func_02083d4ctt)

// dushInitCheck (0x0203ed84): 1 when none of the four cells ahead is blocked.
int dushInitCheck(Entity *e) {
    u16 cell;
    u16 i;
    s32 dy;
    s32 dx;
    const s8 *hitbox;

    hitbox = (const s8 *)e->hitbox;
    dy = (e->y.HALF.HI + hitbox[1]) - mapState.originY;
    dx = e->x.HALF.HI - mapState.originX;
    cell = (u16)((dx >> 4) | ((dy >> 4) << 6));
    for (i = 0; i < 4; i++) {
        if (func_02083d4c(cell, e->layer)) {
            return 0;
        }
        cell = (u16)(cell + ((const u16 *)cellDeltaTable)[e->direction >> 3]);
    }
    return 1;
}
