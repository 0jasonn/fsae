#include "engine/functions.h"
#include "global.h"
#include "enemy/bgobj.h"

// Functions in this file: bgobj_moveset (0x0203e720).

ARM void bgobj_moveset(Entity *e, u8 direction) {
    e->action = 3;
    e->direction = direction & 0x1f;
    e->timer = bgobj_moveTimerTable[Random() & 3];
    e->animationState = 2;
    InitAnimationForceUpdate(e, 2);
}
