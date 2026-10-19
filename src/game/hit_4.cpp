#include "engine/functions.h"
#include "global.h"
#include "object/template.h"
#include "game/hitdecls.h"

// Tate hit handlers (module hit, fourth unit). Original names from the debug build:
//   hit_tateorghajiki, hit_tatetgthajiki
// The template of the object's type gets invincibility 0x80 when it has none.
#define HIT_KNOCKBACK_FRAMES(k) (((k) & 0x80) ? ((s8)(k) + (s8)(k) / 4) : -((s8)(k) + (s8)(k) / 4))

// Original-side tate hit: e takes the knockback of t and the frames of t, the template and t are given invincibility.
ARM BOOL hit_tateorghajiki(Entity *e, Entity *t, u8 unused) {
    e->unk_42 = *(u8 *)&t->attackKnockback;
    e->iframes = HIT_KNOCKBACK_FRAMES(*(u8 *)&t->attackKnockback);
    if (OBJ_TEMPLATE(e->type)->iframes == 0) {
        OBJ_TEMPLATE(e->type)->iframes = 0x80;
    }
    nakamaCheckTgtOnly(t, e);
    if (t->iframes == 0) {
        t->iframes = 0xff;
    }
    shiledCheck(e, t);
    return 1;
}

// Target-side tate hit: t takes the knockback of e and the frames of e; the template and e are given invincibility.
ARM BOOL hit_tatetgthajiki(Entity *e, Entity *t, u8 unused) {
    t->unk_42 = *(u8 *)&e->attackKnockback;
    t->iframes = HIT_KNOCKBACK_FRAMES(*(u8 *)&e->attackKnockback);
    if (OBJ_TEMPLATE(t->type)->iframes == 0) {
        OBJ_TEMPLATE(t->type)->iframes = 0x80;
    }
    if (e->iframes == 0) {
        e->iframes = 0xff;
    }
    return 1;
}
