#include "engine/functions.h"
#include "global.h"
#include "enemy/em19.h"

// Functions in this file: em19_atafutainit (0x0203e4e4), em19_atafutawait (0x0203e520), em19_atafuta (0x0203e55c).

ARM void em19_atafutainit(Entity *e) {
    e->action = 8;
    e->timer = 0xf;
    e->spriteSettings.b0 = 1;
    e->poseId = 6;
    e->animationState = 2;
    InitAnimationForceUpdate(e, 2);
}

ARM void em19_atafutawait(Entity *e) {
    if (e->timer != 0) {
        e->timer--;
        return;
    }
    if (UpdateGravity(e, 0x2000) == 0) {
        e->action = 9;
        e->timer = 1;
    }
}

ARM void em19_atafuta(Entity *e) {
    if (--e->timer == 0) {
        e->direction = (Random() & 0x18) + 4;
    }
    func_020847b0(e);
    func_02085990(e);
}
