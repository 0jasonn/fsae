#include "engine/entity.h"
#include "global.h"

ARM void seqset(Entity *e, int dir) {
    if ((e->animationState & 0xe) == dir) {
        if ((e->direction & 0xf) == 0 || (e->animationState & 1) == (e->direction >> 4)) {
            return;
        }
        InitAnimationForceUpdate(e, e->animationState = dir + (e->direction >> 4));
        return;
    }
    InitAnimationForceUpdate(e, e->animationState = dir + (e->animationState & 1));
}
