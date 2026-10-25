#include "engine/functions.h"
#include "global.h"
#include "enemy/em17_3.h"

// Functions in this file: em17_ball (0x0203daac), em17_standup (0x0203dad4).

ARM void em17_ball(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (buruburu(e) != 0) {
        func_02089524(e);
    }
}

ARM void em17_standup(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (e->frame & 0x80) {
        e->action = 1;
        e->timer = 1;
        e->animationState = 0;
        InitAnimationForceUpdate(e, 0);
    }
}
