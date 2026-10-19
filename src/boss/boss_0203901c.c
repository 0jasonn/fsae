#include "boss/boss_02038544.h"
#include "global.h"

ARM void em05_jump1(Entity *e) {
    func_020847c8(e);
    UpdateGravity(e, 0x1400);
    UpdateAnimationSingleFrame(e);
    if ((e->frame & 0x80) == 0) {
        return;
    }
    e->action++;
    e->timer = 0xc;
    InitAnimationForceUpdate(e, e->animationState + 8);
}
