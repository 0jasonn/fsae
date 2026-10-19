#include "engine/functions.h"
#include "engine/entity.h"
#include "global.h"

ARM void seqset(Entity *e, int baseAnim) {
    if ((e->animationState & 0xe) == baseAnim) {
        if ((e->direction & 0xf) == 0 || (e->animationState & 1) == (e->direction >> 4)) {
            return;
        }
        InitAnimationForceUpdate(e, e->animationState = baseAnim + (e->direction >> 4));
        return;
    }
    InitAnimationForceUpdate(e, e->animationState = baseAnim + (e->animationState & 1));
}
