#include "engine/functions.h"
#include "global.h"
#include "actor/enemy/em16.h"

// em16_getdir (0x0203d1a4): starts the walk action with a random wait time and picks the walk direction: towards the
// target when there is one (rounded to a quarter turn), random otherwise.
void em16_getdir(Entity *e) {
    e->action = 4;
    e->timer = em16_timerTable[Random() & 3];
    if (V(e)->target == NULL) {
        e->direction = Random() & 0x18;
    } else {
        e->direction = (GetFacingDirection(e, V(e)->target) + 4) & 0x18;
    }
    e->animationState = e->direction >> 3;
    InitAnimationForceUpdate(e, e->animationState + 8);
}
