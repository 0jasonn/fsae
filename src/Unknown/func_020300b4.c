#include "Unknown/Entity.h"
#include "global.h"

ARM void func_020300b4(Entity *e, int dir) {
    if ((e->animationState & 0xe) == dir) {
        if ((e->direction & 0xf) == 0 || (e->animationState & 1) == (e->direction >> 4)) {
            return;
        }
        InitAnimationForceUpdate(e, e->animationState = dir + (e->direction >> 4));
        return;
    }
    InitAnimationForceUpdate(e, e->animationState = dir + (e->animationState & 1));
}
