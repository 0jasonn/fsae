#include "engine/functions.h"
#include "enemy/em03.h"
#include "global.h"

ARM void em04_dush(Entity *e) {
    if (e->timer != 0) {
        e->timer--;
        return;
    }
    UpdateAnimationSingleFrame(e);
    if (func_020847a0(e) != 0) {
        return;
    }
    e->action = 1;
    e->speed = 0x80;
    e->subtimer = 0x14;
    InitAnimationForceUpdate(e, e->animationState);
}

ARM void em05_main(Entity *e) {
    EnemyFunctionHandler(e, em05_actions);
}

ARM void em05_normal(Entity *e) {
    em05_typeActions[e->type][e->action](e);
}
