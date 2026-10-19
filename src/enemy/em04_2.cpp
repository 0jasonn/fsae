#include "engine/functions.h"
#include "enemy/em03.h"
#include "global.h"

ARM void em04_getdir(Entity *e) {
    e->action++;
    e->timer = (Random() & 0x30) + 0x3c;
    e->direction = Random() & 0x18;
    u8 anim = EmCharDir4(e->direction);
    if (anim == e->animationState) {
        return;
    }
    e->animationState = anim;
    InitAnimationForceUpdate(e, anim);
}
