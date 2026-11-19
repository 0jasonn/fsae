#include "engine/functions.h"
#include "global.h"
#include "game/hitdecls.h"
#include "game/hit_tartnuck.h"

// Hit handler of the tart nut (module hit). Original name from the debug build: hit_tartnuck.
// A hit from the side the tart nut guards (table lookup by the animation state) bounces both objects, any other hit
// damages the target.

extern const u8 data_020ce53c[]; // guarded side per animation state

#define HIT_KNOCKBACK_FRAMES(k) (((k) & 0x80) ? ((s8)(k) + (s8)(k) / 4) : -((s8)(k) + (s8)(k) / 4))
#define HIT_KNOCKBACK_FRAMES_SHORT(k) (((k) & 0x80) ? (-16 - (s8)(k)) : ((s8)(k) + 16))

BOOL hit_tartnuck(Entity *e, Entity *t, u8 mode) {
    mode = (((mode ^ 0x10) + 4) & 0x18) >> 3;
    if (data_020ce53c[t->animationState] == mode) {
        e->iframes = HIT_KNOCKBACK_FRAMES(*(u8 *)&t->attackKnockback);
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
