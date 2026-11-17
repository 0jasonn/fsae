#include "engine/functions.h"
#include "global.h"
#include "game/hitdecls.h"
#include "game/hit_front.h"

// Hit handlers of the front-guard objects (module hit). Original names from the debug build: hit_frontmuteki,
// hit_frontmuteki2. The hit direction is compared with the facing direction derived from mode (the guard faces within
// 0x18 steps of the mode direction); a guarded hit bounces both sides, an unguarded one damages the target.

// Invincibility frames of a hit with knockback byte k (0x80 set: k + k / 4, else the negation).
#define HIT_KNOCKBACK_FRAMES(k) (((k) & 0x80) ? ((s8)(k) + (s8)(k) / 4) : -((s8)(k) + (s8)(k) / 4))
// Same for the short form: -16 - k when bit 7 is set, k + 16 otherwise.
#define HIT_KNOCKBACK_FRAMES_SHORT(k) (((k) & 0x80) ? (-16 - (s8)(k)) : ((s8)(k) + 16))

BOOL hit_frontmuteki(Entity *e, Entity *t, u8 mode) {
    s32 direction;

    mode = ((mode ^ 0x10) - 0xc) & 0x1f; // direction the guard faces
    direction = (t->direction - mode) & 0x1f;
    if (direction <= 0x18) {
        e->unk_42 = *(u8 *)&t->attackKnockback;
        e->iframes = HIT_KNOCKBACK_FRAMES(*(u8 *)&t->attackKnockback);
        t->unk_42 = *(u8 *)&e->attackKnockback;
        t->iframes = HIT_KNOCKBACK_FRAMES(*(u8 *)&e->attackKnockback);
        setKokin(e, t);
    } else {
        t->health = decVital(t, e);
        t->unk_42 = *(u8 *)&e->attackKnockback;
        t->iframes = HIT_KNOCKBACK_FRAMES_SHORT(*(u8 *)&t->attackKnockback);
        if (e->iframes == 0) {
            e->iframes = 0xff;
        }
    }
    return 1;
}

BOOL hit_frontmuteki2(Entity *e, Entity *t, u8 mode) {
    s32 direction;

    mode = ((mode ^ 0x10) - 0xc) & 0x1f;
    direction = (t->direction - mode) & 0x1f;
    if (direction <= 0x18) {
        e->iframes = HIT_KNOCKBACK_FRAMES(*(u8 *)&t->attackKnockback);
        t->iframes = HIT_KNOCKBACK_FRAMES(*(u8 *)&e->attackKnockback);
        setKokin(e, t);
    } else {
        t->unk_42 = *(u8 *)&e->attackKnockback;
        t->iframes = *(u8 *)&e->attackKnockback; // overwritten below, kept for the match
        t->iframes = HIT_KNOCKBACK_FRAMES(*(u8 *)&e->attackKnockback);
        t->unk_43 = 0xf0;
        if (e->iframes == 0) {
            e->iframes = 0xff;
        }
    }
    return 1;
}
