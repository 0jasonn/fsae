#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "actor/enemy/em12.h"

// Functions in this file (actor em12, original name em12_damage):
//   em12_damage

extern const u8 em12_actions[]; // knockback table of em12 (dsd name)

// Damage: a contact from a partner player that faces the actor (contact flag 0x95) with the matching direction and
// distance costs one health and gives the actor 0xf frames of invincibility; then the generic knockback runs.
void em12_damage(Entity *e) {
    Entity *partner;
    s32 gap;

    if (e->contactFlags != 0x95) {
        goto knockback;
    }
    u8 anim = e->animationState;
    partner = e->contactedEntity;
    if (e->animationState != ((((partner->direction + 4) & 0x18) ^ 0x10) >> 3)) {
        goto knockback;
    }
    if ((anim & 1) != 0) {
        gap = partner->y.HALF.HI + partner->z.HALF.HI - e->y.HALF.HI - e->z.HALF.HI;
        if ((u32)(gap + 8) >= 0x11) {
            goto knockback;
        }
        goto hit;
    }
    gap = partner->x.HALF.HI - e->x.HALF.HI;
    if ((u32)(gap + 8) >= 0x11) {
        goto knockback;
    }
hit:
    e->health -= 1;
    e->iframes = 0xf;
    EnqueueSFX(4);
knockback:
    GenericKnockback(e, em12_actions);
}

// Original names: em12_init, em12_wait (em12_wait2 is in scratch/agentA/nonmatching/em12_wait2.c)

void em12_init(Entity *e) {
    e->action = 1;
    e->unk_2e = 0xe;
    e->hitbox = em12_hitbox;
    V(e)->w70.typeBits = ParseTypeBits(e->type);
    V(e)->areaX = ((e->x.HALF.HI & 0xfc0) >> 2) + mapState.unk_18 + data_0213492c[e->areaIndex * 2];
    V(e)->areaW = ((((u32)e->x.HALF.HI) << 26) >> 22) + 0x20;
    V(e)->areaY = ((e->y.HALF.HI & 0xfc0) >> 2) + mapState.unk_1a + em12_spawnOffsetY[e->areaIndex * 2];
    V(e)->areaH = ((((u32)e->y.HALF.HI) << 26) >> 22) + 0x20;
    e->x.HALF.HI = (e->type2 << 4) + mapState.unk_18 + data_0213492c[e->areaIndex * 2];
    V(e)->homeX = e->x.HALF.HI;
    e->y.HALF.HI = mapState.unk_1a + (e->timer << 4) + em12_spawnOffsetY[e->areaIndex * 2];
    V(e)->homeY = e->y.HALF.HI;
    func_0208ae30(e);
    e->spriteSettings.b20 = GetObjColor(em12_colorByPlayer[gameState.unk_01]);
    e->spriteSettings.b16 = e->spriteSettings.b20;
}

void em12_wait(Entity *e) {
    if ((V(e)->w70.typeBits & em12_typeMasks[e->areaIndex]) == V(e)->w70.typeBits) {
        e->action = 2;
    }
}
