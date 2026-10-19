#include "engine/functions.h"
#include "global.h"
#include "game/hitdecls.h"

// Hit handlers, second hit unit (module hit). Original names from the debug build:
//   hit_jelly, hit_tgtstop, hit_plhajiki, hit_orgdamageonly, hit_tgtdamageonly, hit_damageonly, hit_orgdie, hit_tgtdie,
//   hit_tgtstoponly, hit_wanwan
// Invincibility frames of a hit with knockback byte k: -16 - k when bit 7 is set, k + 16 otherwise.
// Field of the plhajiki hit, at 0x70 of the entity (inside the actor-specific bytes).
typedef struct Vars_PlHit {
    u8 unk_00[0x70];
    u8 pushValue; // 0x70: knockback value of the other side, set by hit_plhajiki
} Vars_PlHit;

#define HIT_KNOCKBACK_FRAMES(k) (((k) & 0x80) ? ((s8)(k) + (s8)(k) / 4) : -((s8)(k) + (s8)(k) / 4))
#define HIT_KNOCKBACK_SIMPLE(k) (((k) & 0x80) ? (-16 - (s8)(k)) : ((s8)(k) + 16))

// Jelly hit: ignored (only t loses its status bit) when the type's flags have 0x60 set, otherwise e takes the knockback.
ARM BOOL hit_jelly(Entity *e, Entity *t, u8 unused) {
    if (data_0212cece[e->type * 0x94] & 0x60) {
        t->statusFlags &= 0x7f;
    } else {
        e->unk_42 = *(u8 *)&t->attackKnockback;
        e->iframes = HIT_KNOCKBACK_FRAMES(*(u8 *)&t->attackKnockback);
    }
    return 1;
}

// Stop hit on t: t takes its damage from e and the frames of e, and is stopped for 0xf0 frames.
ARM BOOL hit_tgtstop(Entity *e, Entity *t, u8 unused) {
    t->health = decVital(t, e);
    t->unk_42 = *(u8 *)&e->attackKnockback;
    t->iframes = *(u8 *)&e->attackKnockback;
    t->iframes = HIT_KNOCKBACK_SIMPLE(*(u8 *)&e->attackKnockback);
    t->unk_43 = 0xf0;
    if (e->iframes == 0) {
        e->iframes = 0xff;
    }
    return 1;
}

// Plhajiki hit: only in wireless mode and when neither side is flagged; each side takes the sign-folded knockback of the
// other.
ARM BOOL hit_plhajiki(Entity *e, Entity *t, u8 unused) {
    s32 folded;

    if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) != 0 && VARS(Vars_PlHit, e)->pushValue == 0 &&
        VARS(Vars_PlHit, t)->pushValue == 0) {
        e->unk_42 = *(u8 *)&t->attackKnockback;
        folded = (*(u8 *)&t->attackKnockback & 0x80) ? (s8)(*(u8 *)&t->attackKnockback) : -(s8)(*(u8 *)&t->attackKnockback);
        VARS(Vars_PlHit, e)->pushValue = folded;
        t->unk_42 = *(u8 *)&e->attackKnockback;
        folded = (*(u8 *)&e->attackKnockback & 0x80) ? (s8)(*(u8 *)&e->attackKnockback) : -(s8)(*(u8 *)&e->attackKnockback);
        VARS(Vars_PlHit, t)->pushValue = folded;
        return 1;
    }
    return 0;
}

// Original-side damage only: e takes its damage from t and the frames of t's knockback; t is given invincibility if none.
ARM BOOL hit_orgdamageonly(Entity *e, Entity *t, u8 unused) {
    e->health = decVital(e, t);
    e->iframes = HIT_KNOCKBACK_SIMPLE(*(u8 *)&t->attackKnockback);
    if (t->iframes == 0) {
        t->iframes = 0xff;
    }
    return 1;
}

// Target-side damage only: t takes its damage from e and the frames of e's knockback; kind 3 objects get the flag.
ARM BOOL hit_tgtdamageonly(Entity *e, Entity *t, u8 unused) {
    t->health = decVital(t, e);
    t->iframes = HIT_KNOCKBACK_SIMPLE(*(u8 *)&e->attackKnockback);
    if (t->objKind == 3) {
        t->unk_42 = 1;
    }
    if (e->iframes == 0) {
        e->iframes = 0xff;
    }
    return 1;
}

// Damage to both sides: e and t each take their damage and the frames of the other's knockback.
ARM BOOL hit_damageonly(Entity *e, Entity *t, u8 unused) {
    e->health = decVital(e, t);
    e->iframes = HIT_KNOCKBACK_SIMPLE(*(u8 *)&t->attackKnockback);
    t->health = decVital(t, e);
    t->iframes = HIT_KNOCKBACK_SIMPLE(*(u8 *)&e->attackKnockback);
    if (t->objKind == 3) {
        t->unk_42 = 1;
    }
    return 1;
}

// Original-side death: e loses its health and status bit; t gets invincibility if none.
ARM BOOL hit_orgdie(Entity *e, Entity *t, u8 unused) {
    e->health = 0;
    e->statusFlags &= 0x7f;
    if (t->iframes == 0) {
        t->iframes = 0xff;
    }
    return 1;
}

// Target-side death: t loses its health and status bit; e gets invincibility if none.
ARM BOOL hit_tgtdie(Entity *e, Entity *t, u8 unused) {
    t->health = 0;
    t->statusFlags &= 0x7f;
    if (e->iframes == 0) {
        e->iframes = 0xff;
    }
    return 1;
}

// Target stop without damage: t is stopped for 0xf0 frames; e gets invincibility if none.
ARM BOOL hit_tgtstoponly(Entity *e, Entity *t, u8 unused) {
    t->iframes = 0xf0;
    t->unk_43 = 0xf0;
    if (e->iframes == 0) {
        e->iframes = 0xff;
    }
    return 1;
}

// Wanwan hit: as hit_tgtdie.
ARM BOOL hit_wanwan(Entity *e, Entity *t, u8 unused) {
    u8 flags;

    flags = t->statusFlags;
    t->health = 0;
    t->statusFlags = flags & 0x7f;
    if (e->iframes == 0) {
        e->iframes = 0xff;
    }
    return 1;
}
