#include "engine/functions.h"
#include "global.h"
#include "actor/enemy/em1c.h"

// charMove (0x0202fa80): when the quadrant the child faces (looked up from the child's direction) or the facing direction
// of the enemy changed, caches both and restarts the animation for the new pair.
void charMove(Entity *e, u8 mode) {
    int quadrant = em1c_charAnimTable[((e->child->direction + 4) & 0x18) >> 3];
    if (quadrant == VARS(Vars_Em1c, e)->cachedQuadrant && (e->direction >> 3) == e->animationState) {
        return;
    }
    VARS(Vars_Em1c, e)->cachedQuadrant = quadrant;
    e->animationState = e->direction >> 3;
    InitAnimationForceUpdate(e, mode + (e->animationState << 2) + VARS(Vars_Em1c, e)->cachedQuadrant);
}
