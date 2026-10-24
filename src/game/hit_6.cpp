#include "engine/functions.h"
#include "global.h"
#include "game/hitdecls.h"
#include "game/hit_6.h"

// Hit handlers of the module hit (sixth unit). Original names from the debug build:
//   hit_tatehajiki (hit_tatehajiki(OBJ_WORK_*, OBJ_WORK_*, unsigned char)), hit_firerobe (hit_firerobe(...))
// Knockback frames: positive knockback gives sk + sk/4, otherwise the negated value.
#define HIT_KNOCKBACK_FRAMES(k) (((k) & 0x80) ? ((s8)(k) + (s8)(k) / 4) : -((s8)(k) + (s8)(k) / 4))
// Knockback frames of a hit on the fire and ice objects: -16 - sk for negative knockback, else sk + 16.
#define HIT_KNOCKBACK_FRAMES_SHORT(k) (((k) & 0x80) ? (-16 - (s8)(k)) : ((s8)(k) + 16))
// The damage object of an entity type, stored at PlayerData stride 0x94.
#define HIT_DAMAGE_OBJECT(e) (*(Entity **)&data_0212ced8[(e)->type * 0x94])

ARM BOOL hit_tatehajiki(Entity *e, Entity *t, u8 unused) {
    if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) == 0) {
        if (Knife_Single_SinglePlay_GetInstance()[1] != 0) {
            if (t->objKind == 1 && e->objKind == 8 && e->type < 2) {
                return FALSE;
            }
        }
    }
    e->unk_42 = *(u8 *)&t->attackKnockback;
    e->iframes = HIT_KNOCKBACK_FRAMES(*(u8 *)&t->attackKnockback);
    if (e->objKind == 8) {
        if (HIT_DAMAGE_OBJECT(e)->iframes == 0) {
            HIT_DAMAGE_OBJECT(e)->iframes = 0x80;
        }
    }
    t->unk_42 = *(u8 *)&e->attackKnockback;
    t->iframes = HIT_KNOCKBACK_FRAMES(*(u8 *)&e->attackKnockback);
    if (t->objKind == 8) {
        if (HIT_DAMAGE_OBJECT(t)->iframes == 0) {
            HIT_DAMAGE_OBJECT(t)->iframes = 0x80;
        }
    }
    nakamaCheck(e, t);
    return 1;
}

ARM BOOL hit_firerobe(Entity *e, Entity *t, u8 mode) {
    Entity *fire;

    if ((*(u16 *)&data_0212cee6[e->type * 0x94] & 0x1401) == 0) {
        fire = GetSetWork(0x55, 1, 0);
        if (fire != NULL) {
            fire->child = e;
            *(u16 *)&data_0212cee6[e->type * 0x94] = 0x400;
            e->animationState = (mode ^ 0x10) >> 2;
        }
    }
    e->unk_42 = *(u8 *)&t->attackKnockback;
    e->iframes = HIT_KNOCKBACK_FRAMES_SHORT(*(u8 *)&t->attackKnockback);
    if (t->iframes == 0) {
        t->iframes = 0xff;
    }
    return 1;
}
