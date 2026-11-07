#include "engine/functions.h"
#include "global.h"
#include "actor/enemy/em16.h"
// em16_move (0x0203d218): walking state; picks a new random direction when the front is blocked, otherwise counts the
// timer down and goes looking (kyoroSet) when it ends.
void em16_move(Entity *e) {
    u8 newDir;
    int animIndex;

    UpdateAnimationSingleFrame(e);
    if (!frontCheck(e)) {
        return;
    }
    if (func_020847a0(e) == 0) {
        newDir = Random() & 0x18;
        if (e->direction == newDir) {
            return;
        }
        animIndex = newDir >> 3;
        e->direction = newDir;
        e->animationState = animIndex;
        InitAnimationForceUpdate(e, e->animationState + 8);
        return;
    }
    e->timer--;
    if (e->timer == 0) {
        kyoroSet(e);
    }
}
