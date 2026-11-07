#include "engine/functions.h"
#include "global.h"

// em01 actor, third unit: em01_slowdown (0x0202eabc), between em01_move and em01_stop.

void dirSeqSet(Entity *e);

// Slowing down before the stop: when the timer runs out switches to the next action (stop pose), otherwise reduces the
// speed down to 0x10 and changes direction when the way is blocked.
void em01_slowdown(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (--e->timer == 0) {
        e->action++;
        InitAnimationForceUpdate(e, e->animationState + 2);
        return;
    }
    if (e->speed > 0x10) {
        e->speed -= 2;
    }
    if (func_020847f8(e) == 0) {
        return;
    }
    dirSeqSet(e);
}
