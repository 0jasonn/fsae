#include "engine/functions.h"
#include "global.h"
#include "game/hitdecls.h"

// Hit and damage helpers (module hit). Original names from the debug build:
//   decVital, shiledCheck, nakamaCheckTgtOnly, nakamaCheck, setKokin

extern u8 data_0212ceb0[]; // one 0x94-byte entry per type (template data), read at offset 0x3e

// Damage of a hit on e from t: deals the damage to the health (or heart), plays the hit sound for some kinds and returns
// the damage left when it is positive.
ARM u8 decVital(Entity *e, Entity *t) {
    s32 damage;
    u8 *typeEntry;

    if (e->objKind == 1) {
        typeEntry = data_0212ceb0 + e->type * 0x94;
        damage = t->attackDamage - (s32)((u32)(typeEntry[0x3e] << 28) >> 30);
        if (damage <= 1) {
            damage = 1;
        }
        damage = -(s8)damage;
        damage = AddHeart(e, (s16)damage);
        func_02085f98(e, 0xc3);
    } else {
        damage = (s16)(e->health - t->attackDamage);
        if (e->objKind == 3) {
            if (e->unk_6a != 0) {
                func_02085f98(e, 0x2d);
            } else {
                func_02085f98(e, 4);
            }
        }
    }
    if (damage <= 0) {
        e->statusFlags &= 0x7f;
        return 0;
    }
    return (u8)damage;
}

// Halves the invincibility frames and the second timer of the object that holds the shield: e when e is kind 8 with id 9,
// otherwise t.
ARM void shiledCheck(Entity *e, Entity *t) {
    if (e->objKind == 8 && e->objId == 9) {
        e->iframes = (s8)e->iframes >> 1;
        e->unk_42 = (s8)e->unk_42 >> 1;
    } else {
        t->iframes = (s8)t->iframes >> 1;
        t->unk_42 = (s8)t->unk_42 >> 1;
    }
}

// Scales the invincibility of t by three quarters when t is a kind 8 or 1 object and e is a kind 8 or 1 object.
ARM void nakamaCheckTgtOnly(Entity *e, Entity *t) {
    s8 frames;

    if (e->objKind != 8 && e->objKind != 1) {
        return;
    }
    if (t->objKind != 8 && t->objKind != 1) {
        return;
    }
    frames = t->iframes;
    t->iframes = (frames >> 1) + (frames >> 2);
    frames = t->unk_42;
    t->unk_42 = (frames >> 1) + (frames >> 2);
}

// Scales the invincibility of both objects by three quarters when both are kind 8 or 1 objects.
ARM void nakamaCheck(Entity *e, Entity *t) {
    s8 frames;

    if (e->objKind != 8 && e->objKind != 1) {
        return;
    }
    if (t->objKind != 8 && t->objKind != 1) {
        return;
    }
    frames = e->iframes;
    e->iframes = (frames >> 1) + (frames >> 2);
    frames = e->unk_42;
    e->unk_42 = (frames >> 1) + (frames >> 2);
    frames = t->iframes;
    t->iframes = (frames >> 1) + (frames >> 2);
    frames = t->unk_42;
    t->unk_42 = (frames >> 1) + (frames >> 2);
}

// Spawns an object of kind 0xf between e and t: the position and layer are the average of the two.
ARM void setKokin(Entity *e, Entity *t) {
    Entity *child;

    child = GetSetWork(0xf, 0x10, 0);
    if (child == NULL) {
        return;
    }
    child->x.HALF.HI = (e->x.HALF.HI + t->x.HALF.HI) >> 1;
    child->y.HALF.HI = (e->y.HALF.HI + t->y.HALF.HI) >> 1;
    child->z.HALF.HI = (e->z.HALF.HI + t->z.HALF.HI) >> 1;
    child->layer = e->layer;
    func_0208ae78(child);
}
