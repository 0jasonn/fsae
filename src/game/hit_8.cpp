#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"
#include "game/hitdecls.h"
#include "game/hit_6.h"

// Damage electric hit (module hit, eighth unit). Original name: hit_dengekidamage.
#define HIT_KNOCKBACK_FRAMES_SHORT(k) (((k) & 0x80) ? (-16 - (s8)(k)) : ((s8)(k) + 16))
#define HIT_DAMAGE_OBJECT(e) (playerWork[(e)->type].entity)

BOOL hit_dengekidamage(Entity *e, Entity *t, u8 mode) {
    HIT_DAMAGE_OBJECT(e)->contactFlags = t->unk_40 | 0x80;
    HIT_DAMAGE_OBJECT(e)->iframes = HIT_KNOCKBACK_FRAMES_SHORT(*(u8 *)&t->attackKnockback);
    HIT_DAMAGE_OBJECT(e)->unk_42 = *(u8 *)&t->attackKnockback;
    HIT_DAMAGE_OBJECT(e)->baseDirection = mode ^ 0x10;
    HIT_DAMAGE_OBJECT(e)->health = decVital(HIT_DAMAGE_OBJECT(e), t);
    func_0208ab50(e);
    if (t->iframes == 0) {
        t->iframes = 0xff;
    }
    return 1;
}

// Trap kokin hit (module hit, fifth unit). Original name: hit_trapkokin.
#define HIT_KNOCKBACK_FRAMES(k) (((k) & 0x80) ? ((s8)(k) + (s8)(k) / 4) : -((s8)(k) + (s8)(k) / 4))

// e takes the frames of t's knockback, t is given invincibility, and the kokin object is set between them.
BOOL hit_trapkokin(Entity *e, Entity *t, u8 unused) {
    e->iframes = HIT_KNOCKBACK_FRAMES(*(u8 *)&t->attackKnockback);
    t->iframes = 0xff;
    setKokin(e, t);
    return 1;
}
