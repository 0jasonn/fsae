#include "engine/functions.h"
#include "global.h"
#include "actor/object/tama05.h"

// hasshaSet (0x0207ea54): launches the projectile: action 2, visible to hits (0x80), moved by the (dx, dy) step of its
// facing, detached from its parent; starts the facing animation (+4) and plays the sound of its type.
void hasshaSet(Entity *e) {
    e->action = 2;
    e->statusFlags |= 0x80;
    e->x.HALF.HI += data_020dccbc[e->animationState * 2];
    e->y.HALF.HI += data_020dccbc[e->animationState * 2 + 1];
    e->parent = NULL;
    InitAnimationForceUpdate(e, e->animationState + 4);
    EnqueueSFX(data_020dcccc[e->type]);
}
