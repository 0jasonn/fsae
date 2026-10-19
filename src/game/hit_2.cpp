#include "engine/functions.h"
#include "global.h"
#include "object/template.h"
#include "game/hitdecls.h"

// Hit handlers (module hit, second unit). Original names from the debug build:
//   hit_orgdamage, hit_tgtdamage, hit_damage
// The invincibility given by a hit depends on the attack knockback k: -16 - k when k is negative, k + 16 otherwise.

// Original-side hit: the attacker e takes its damage from t and gets the knockback of t.
ARM BOOL hit_orgdamage(Entity *e, Entity *t, u8 unused) {
    e->health = decVital(e, t);
    e->unk_42 = (*(u8 *)&t->attackKnockback);
    if ((*(u8 *)&t->attackKnockback) & 0x80) {
        e->iframes = -16 - (s8)(*(u8 *)&t->attackKnockback);
    } else {
        e->iframes = (s8)(*(u8 *)&t->attackKnockback) + 16;
    }
    if (t->iframes == 0) {
        t->iframes = 0xff;
    }
    return 1;
}

// Target-side hit: t takes its damage from e and the knockback of e.
ARM BOOL hit_tgtdamage(Entity *e, Entity *t, u8 unused) {
    t->health = decVital(t, e);
    t->unk_42 = (*(u8 *)&e->attackKnockback);
    if ((*(u8 *)&t->attackKnockback) & 0x80) {
        t->iframes = -16 - (s8)(*(u8 *)&t->attackKnockback);
    } else {
        t->iframes = (s8)(*(u8 *)&t->attackKnockback) + 16;
    }
    if (e->iframes == 0) {
        e->iframes = 0xff;
    }
    return 1;
}

// Both sides take the hit: e from t and t from e.
ARM BOOL hit_damage(Entity *e, Entity *t, u8 unused) {
    s32 frames;

    e->health = decVital(e, t);
    e->unk_42 = (*(u8 *)&t->attackKnockback);
    if ((*(u8 *)&t->attackKnockback) & 0x80) {
        frames = -16 - (s8)(*(u8 *)&t->attackKnockback);
    } else {
        frames = (s8)(*(u8 *)&t->attackKnockback) + 16;
    }
    e->iframes = frames;
    t->health = decVital(t, e);
    t->unk_42 = (*(u8 *)&e->attackKnockback);
    if ((*(u8 *)&t->attackKnockback) & 0x80) {
        t->iframes = -16 - (s8)(*(u8 *)&t->attackKnockback);
    } else {
        t->iframes = (s8)(*(u8 *)&t->attackKnockback) + 16;
    }
    return 1;
}

// Invincibility frames of a hit with the knockback byte k (bit 7 selects the sign of the result).
#define HIT_KNOCKBACK_FRAMES(k) (((k) & 0x80) ? ((s8)(k) + (s8)(k) / 4) : -((s8)(k) + (s8)(k) / 4))

// Original-side hajiki hit: from the wireless check, kind 1 against kind 8 with a type below 2 is ignored; otherwise the
// hit applies the knockback of t to e and then e's knockback to t.
ARM BOOL hit_orghajiki(Entity *e, Entity *t, u8 unused) {
    if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) == 0 && Knife_Single_SinglePlay_GetInstance()[1] != 0) {
        if (e->objKind == 1 && t->objKind == 8 && t->type < 2) {
            return 0;
        }
    }
    e->unk_42 = *(u8 *)&t->attackKnockback;
    e->iframes = HIT_KNOCKBACK_FRAMES(*(u8 *)&t->attackKnockback);
    nakamaCheckTgtOnly(t, e);
    if (t->iframes == 0) {
        t->iframes = 0xff;
    }
    shiledCheck(e, t);
    return 1;
}

// Target-side hajiki hit: from the wireless check, kind 1 against kind 8 with a type below 2 is ignored; otherwise t
// takes the knockback of e and e gets the nakama check.
ARM BOOL hit_tgthajiki(Entity *e, Entity *t, u8 unused) {
    if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) == 0 && Knife_Single_SinglePlay_GetInstance()[1] != 0) {
        if (t->objKind == 1 && e->objKind == 8 && t->type < 2) {
            return 0;
        }
    }
    t->unk_42 = *(u8 *)&e->attackKnockback;
    t->iframes = HIT_KNOCKBACK_FRAMES(*(u8 *)&e->attackKnockback);
    nakamaCheckTgtOnly(e, t);
    if (e->iframes == 0) {
        e->iframes = 0xff;
    }
    return 1;
}

// Hajiki hit between two kind 8 objects with the same id: ignored for ids 1 to 3, otherwise both sides take the other's
// knockback and the nakama check runs.
ARM BOOL hit_hajiki(Entity *e, Entity *t, u8 unused) {
    if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) == 0 && Knife_Single_SinglePlay_GetInstance()[1] != 0) {
        if (e->objKind == 8 && t->objKind == 8 && t->objId == e->objId) {
            if ((u8)(t->objId + 0xff) <= 2) {
                return 0;
            }
        }
    }
    e->unk_42 = *(u8 *)&t->attackKnockback;
    e->iframes = HIT_KNOCKBACK_FRAMES(*(u8 *)&t->attackKnockback);
    t->unk_42 = *(u8 *)&e->attackKnockback;
    t->iframes = HIT_KNOCKBACK_FRAMES(*(u8 *)&e->attackKnockback);
    nakamaCheck(e, t);
    return 1;
}

// Item hit: an item (kind 6, id 0) that hits the player is cleared of its flag and adds its item, otherwise t is cleared
// and the item of e's type is added.
ARM BOOL hit_item(Entity *e, Entity *t, u8 unused) {
    if (e->objKind == 6 && e->objId == 0) {
        e->statusFlags &= 0x7f;
        SetItemAdd(e, OBJ_TEMPLATE(t->type));
    } else {
        t->statusFlags &= 0x7f;
        SetItemAdd(t, OBJ_TEMPLATE(e->type));
    }
    return 2;
}

// Kokin hit: e takes the frames of t's knockback and t those of e, then the kokin object is set between them.
ARM BOOL hit_kokin(Entity *e, Entity *t, u8 unused) {
    e->iframes = HIT_KNOCKBACK_FRAMES(*(u8 *)&t->attackKnockback);
    t->iframes = HIT_KNOCKBACK_FRAMES(*(u8 *)&e->attackKnockback);
    setKokin(e, t);
    return 1;
}

// Original-side kokin hit: e takes the knockback of t as its damage knockback and the frames of both.
ARM BOOL hit_orgkokin(Entity *e, Entity *t, u8 unused) {
    e->unk_42 = *(u8 *)&t->attackKnockback;
    e->iframes = HIT_KNOCKBACK_FRAMES(*(u8 *)&t->attackKnockback);
    t->iframes = HIT_KNOCKBACK_FRAMES(*(u8 *)&e->attackKnockback);
    setKokin(e, t);
    return 1;
}

// Target-side kokin hit: t takes the knockback of e as its damage knockback and the frames of both.
ARM BOOL hit_tgtkokin(Entity *e, Entity *t, u8 unused) {
    t->unk_42 = *(u8 *)&e->attackKnockback;
    t->iframes = HIT_KNOCKBACK_FRAMES(*(u8 *)&e->attackKnockback);
    e->iframes = HIT_KNOCKBACK_FRAMES(*(u8 *)&t->attackKnockback);
    setKokin(e, t);
    return 1;
}

// Hajiki kokin hit: both sides take the knockback of the other as damage knockback and frames, then the kokin is set.
ARM BOOL hit_hajikikokin(Entity *e, Entity *t, u8 unused) {
    e->unk_42 = *(u8 *)&t->attackKnockback;
    e->iframes = HIT_KNOCKBACK_FRAMES(*(u8 *)&t->attackKnockback);
    t->unk_42 = *(u8 *)&e->attackKnockback;
    t->iframes = HIT_KNOCKBACK_FRAMES(*(u8 *)&e->attackKnockback);
    setKokin(e, t);
    return 1;
}

// Hit that does nothing but its call (0x02085e08) with the same arguments.
ARM BOOL hit_orghosei(Entity *e, Entity *t, u8 unused) {
    func_02085e08(e, t);
    return 0;
}

// Stale hit: t is set to the stale state for 0xf4 frames; e is given the invincibility when it has none.
ARM BOOL hit_stalescape(Entity *e, Entity *t, u8 unused) {
    t->subAction = 0xff;
    t->iframes = 0xf4;
    if (e->iframes == 0) {
        e->iframes = 0xff;
    }
    return 1;
}
