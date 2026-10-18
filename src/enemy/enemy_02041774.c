#include "enemy/actor_0204112c.h"
#include "global.h"

extern const void *data_020d341c[];

// Enemy_UpdateChildHitbox (0x02041774): picks the child's hitbox from the animation state and frame.
ARM void Enemy_UpdateChildHitbox(Entity *e) {
    if (e->child == NULL) {
        return;
    }
    CopyPosition(e, e->child);
    if ((e->frame & 7) == 0) {
        e->child->unk_3c &= 0x7f;
        return;
    }
    e->child->unk_3c |= 0x80;
    e->child->hitbox = data_020d341c[e->animationState * 5 + (e->frame & 7) - 1];
}
