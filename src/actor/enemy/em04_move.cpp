#include "engine/functions.h"
#include "global.h"
#include "actor/enemy/em04_move.h"

// Functions in this file: em04_move (0x02038bbc).

void em04_move(Entity *e) {
    if (e->subtimer == 0) {
        u32 bits = func_02084ac8(e, 0xc);
        if (bits & 0x80) {
            e->action = 3;
            e->timer = 0x10;
            e->speed = 0x1a0;
            e->direction = bits & 0x18;
            e->animationState = e->direction >> 3;
            InitAnimationForceUpdate(e, e->animationState + 4);
            return;
        }
    } else {
        e->subtimer -= 1;
    }
    if (e->timer == 0) {
        e->action = 1;
        return;
    }
    e->timer -= 1;
    func_020847a0(e);
    UpdateAnimationSingleFrame(e);
}
