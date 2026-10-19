#include "engine/functions.h"
#include "global.h"
#include "game/hitdecls.h"

// Trap kokin hit (module hit, fifth unit). Original name: hit_trapkokin.
#define HIT_KNOCKBACK_FRAMES(k) (((k) & 0x80) ? ((s8)(k) + (s8)(k) / 4) : -((s8)(k) + (s8)(k) / 4))

// e takes the frames of t's knockback, t is given invincibility, and the kokin object is set between them.
ARM BOOL hit_trapkokin(Entity *e, Entity *t, u8 unused) {
    e->iframes = HIT_KNOCKBACK_FRAMES(*(u8 *)&t->attackKnockback);
    t->iframes = 0xff;
    setKokin(e, t);
    return 1;
}
