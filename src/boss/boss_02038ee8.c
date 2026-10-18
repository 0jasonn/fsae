#include "boss/boss_02038544.h"
#include "global.h"

ARM void func_02038ee8(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if ((e->frame & 0x80) == 0) {
        return;
    }
    e->action = 1;
    e->timer = 1;
    e->animationState = 0;
    e->speed = 0x80;
    e->unk_3c &= 0xef;
    e->unk_3f = 9;
    InitAnimationForceUpdate(e, 0);
}
