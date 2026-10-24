#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "enemy/em12.h"

// Functions in this file (actor em12, original name em12_damage):
//   em12_damage

extern const u8 em12_actions[]; // knockback table of em12 (dsd name)

// Damage: a contact from a partner player that faces the actor (contact flag 0x95) with the matching direction and
// distance costs one health and gives the actor 0xf frames of invincibility; then the generic knockback runs.
ARM void em12_damage(Entity *e) {
    Entity *partner;
    s32 gap;

    if (e->contactFlags != 0x95) {
        goto knockback;
    }
    u8 anim = e->animationState;
    partner = e->contactedEntity;
    if (e->animationState != ((((partner->direction + 4) & 0x18) ^ 0x10) >> 3)) {
        goto knockback;
    }
    if ((anim & 1) != 0) {
        gap = partner->y.HALF.HI + partner->z.HALF.HI - e->y.HALF.HI - e->z.HALF.HI;
        if ((u32)(gap + 8) >= 0x11) {
            goto knockback;
        }
        goto hit;
    }
    gap = partner->x.HALF.HI - e->x.HALF.HI;
    if ((u32)(gap + 8) >= 0x11) {
        goto knockback;
    }
hit:
    e->health -= 1;
    e->iframes = 0xf;
    EnqueueSFX(4);
knockback:
    GenericKnockback(e, em12_actions);
}
