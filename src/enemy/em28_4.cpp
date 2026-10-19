#include "engine/functions.h"
#include "enemy/em28.h"
#include "global.h"

extern const void *em28_swordHitboxes[];

// swordMgr (0x02041774): picks the child's hitbox from the animation state and frame.
ARM void swordMgr(Entity *e) {
    if (e->child == NULL) {
        return;
    }
    ObjPosCopy(e, e->child);
    if ((e->frame & 7) == 0) {
        e->child->statusFlags &= 0x7f;
        return;
    }
    e->child->statusFlags |= 0x80;
    e->child->hitbox = em28_swordHitboxes[e->animationState * 5 + (e->frame & 7) - 1];
}
