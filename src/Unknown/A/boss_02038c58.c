#include "Unknown/A/Boss_02038544.h"
#include "global.h"

ARM void func_02038c58(Entity *e) {
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

ARM void func_02038cb0(Entity *e) {
    EnemyFunctionHandler(e, data_020d1a34);
}

ARM void func_02038cc4(Entity *e) {
    data_020d19ec[e->type][e->action](e);
}
