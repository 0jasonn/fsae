#include "boss/boss_02038544.h"
#include "global.h"

ARM void func_02038b68(Entity *e) {
    e->action++;
    e->timer = (Random() & 0x30) + 0x3c;
    e->direction = Random() & 0x18;
    u8 anim = func_02045aa0();
    if (anim == e->animationState) {
        return;
    }
    e->animationState = anim;
    InitAnimationForceUpdate(e, anim);
}
