#include "engine/functions.h"
#include "actor/enemy/em03.h"
#include "global.h"

void em05_land(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if ((e->frame & 0x80) == 0) {
        return;
    }
    e->action = 1;
    e->timer = 1;
    e->animationState = 0;
    e->speed = 0x80;
    e->statusFlags &= 0xef;
    e->poseId = 9;
    InitAnimationForceUpdate(e, 0);
}
