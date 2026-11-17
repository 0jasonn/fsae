#include "engine/functions.h"
#include "global.h"
#include "actor/enemy/em19_move.h"

// Functions in this file: em19_move (0x0203e324).

// Walks along the grid: when the entity is centred on a cell in one axis it waits for the other axis, turns around when
// blocked and starts the next action when centred on both. The returns inside the arms keep the stores separate.
void em19_move(Entity *e) {
    int pos;
    u8 dir;

    func_020847a0(e);
    UpdateAnimationSingleFrame(e);
    if (e->timer != 0) {
        e->timer--;
        return;
    }
    dir = e->direction;
    if ((dir & 8) != 0) {
        if ((e->x.HALF.HI & 0xf) == 8) {
            pos = e->y.HALF.HI & 0xf;
            if (pos == 8) {
                setActionAnim3(e);
                return;
            }
            e->action = 4;
            if (pos < 8) {
                e->direction = 0x10;
                return;
            }
            e->direction = 0;
            return;
        }
        if ((e->wallFlags & 0xee00) != 0) {
            e->direction = dir ^ 0x10;
        }
        return;
    }
    if ((e->y.HALF.HI & 0xf) == 8) {
        pos = e->x.HALF.HI & 0xf;
        if (pos == 8) {
            setActionAnim3(e);
            return;
        }
        e->action = 4;
        if (pos < 8) {
            e->direction = 8;
            return;
        }
        e->direction = 0x18;
        return;
    }
    if ((e->wallFlags & 0xee) != 0) {
        e->direction = dir ^ 0x10;
    }
}
