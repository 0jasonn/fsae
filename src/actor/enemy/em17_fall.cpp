#include "engine/functions.h"
#include "global.h"
#include "actor/enemy/em17_fall.h"

// Functions in this file: em17_fall (0x0203da28).

// The two arms are written out in full: the compiler merges their identical tails.
void em17_fall(Entity *e) {
    switch (func_02086044(e, 0x1800)) {
    case 0:
        e->action = 6;
        VARS(Vars_Em17Fall, e)->shakeTimer = 0x258;
        e->animationState = 5;
        InitAnimationForceUpdate(e, 5);
        EnqueueSFX(0x31);
        break;
    case 1:
        e->animationState = 4;
        InitAnimationForceUpdate(e, 4);
        EnqueueSFX(0x31);
        break;
    }
    if (e->animationState != 4) {
        return;
    }
    if (e->zVelocity >= 0) {
        return;
    }
    e->animationState = 3;
    InitAnimationForceUpdate(e, 3);
}
