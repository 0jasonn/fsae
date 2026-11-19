#include "engine/functions.h"
#include "actor/enemy/em29.h"

// em30_type3 (0x02042abc): a segment of the em30 chain: starts action 1 with animation 6, then every frame places itself
// between its parent and child (type2 = segment number) and, while the child is in the 0x60 or 0xa0 direction and
// flagged, shifts itself to the matching side.
void em30_type3(Entity *e) {
    Entity *parent;
    Entity *child;

    if (e->action == 0) {
        e->action = 1;
        e->spriteSettings.b0 = 1;
        e->unk_2e = 8;
        e->unk_5e.b2 = 3;
        e->statusFlags |= 0x80;
        e->hitbox = data_020d34da;
        InitAnimationForceUpdate(e, 6);
    }
    e->spriteSettings.b30 = 1;
    e->spriteSettings.b14 = e->spriteSettings.b30;
    UpdateAnimationSingleFrame(e);
    parent = e->parent;
    child = e->child;
    s32 quarterX = (child->x.WORD - parent->x.WORD) >> 2;
    e->x.WORD = parent->x.WORD + quarterX * e->type2;
    s32 quarterY = (child->y.WORD - parent->y.WORD) >> 2;
    e->y.WORD = parent->y.WORD + quarterY * e->type2;
    if ((child->unk_6c[6] & 1) == 0) {
        return;
    }
    if (child->direction == 0x60) {
        if (e->type2 == 2) {
            e->x.HALF.HI += 2;
            e->y.HALF.HI -= 4;
        } else {
            e->x.HALF.HI += 4;
            e->y.HALF.HI -= 6;
        }
    } else if (child->direction == 0xa0) {
        if (e->type2 == 2) {
            e->x.HALF.HI -= 2;
            e->y.HALF.HI -= 4;
        } else {
            e->x.HALF.HI -= 4;
            e->y.HALF.HI -= 6;
        }
    }
    e->spriteSettings.b30 = 2;
    e->spriteSettings.b14 = e->spriteSettings.b30;
}
