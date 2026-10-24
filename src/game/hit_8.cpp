#include "engine/functions.h"
#include "global.h"
#include "game/hitdecls.h"
#include "game/hit_6.h"

// Damage electric hit (module hit, eighth unit). Original name: hit_dengekidamage.
#define HIT_KNOCKBACK_FRAMES_SHORT(k) (((k) & 0x80) ? (-16 - (s8)(k)) : ((s8)(k) + 16))
#define HIT_DAMAGE_OBJECT(e) (*(Entity **)&data_0212ced8[(e)->type * 0x94])

ARM BOOL hit_dengekidamage(Entity *e, Entity *t, u8 mode) {
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
