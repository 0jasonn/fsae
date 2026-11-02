#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"
#include "actor/object/sword_move.h"

// Sword actor (module sword). Address -> name:
//   0x0207b190 sword_move (original name): per-frame update of the sword: removal, hit sounds, wave spawn

void sword_move(Entity *e) {
    Entity *owner = data_0212ceb0[e->type].entity;

    if (data_0212ceb0[e->type].weapon != e) {
        func_020841b0(e);
        zFree((void *)e->hitbox);
        PutObjWork(e);
        return;
    }
    if (data_0212ceb0[e->type].inUse == 0) {
        data_0212ceb0[e->type].weapon = NULL;
        data_0212ceb0[e->type].actionFlags = 0;
        func_020841b0(e);
        zFree((void *)e->hitbox);
        PutObjWork(e);
        return;
    }
    if (data_0212ceb0[e->type].inUse & 0x80) {
        func_02085f98(owner, 0x14);
    }
    if (data_0212ceb0[e->type].actionFlags != 0) {
        e->unk_40 = 0xc;
        if (data_0212ceb0[e->type].actionFlags & 0x20) {
            e->spriteSettings.b16 ^= 3;
        }
        if (data_0212ceb0[e->type].actionFlags & 0x40) {
            e->attackDamage = ((SwordLevelView *)&data_0212ceb0[e->type].unk_3e)->level * 2 + 8;
            e->unk_40 = 8;
        }
    }
    sword_plsync(e, owner);
    PlWeaponFireCheck(e);
    swordEvent(e);
    if (data_0212ceb0[e->type].actionFlags == 0) {
        Entity *effect;

        if (((SwordLevelView *)&data_0212ceb0[e->type].unk_3e)->level == 0) {
            return;
        }
        if (!(owner->frame & 0x40)) {
            return;
        }
        effect = GetObjWork();
        if (effect == NULL) {
            return;
        }
        effect->objKind = 6;
        effect->objId = 0xf;
        if (((SwordLevelView *)&data_0212ceb0[e->type].unk_3e)->level == 1) {
            effect->type = 0x14;
        } else {
            effect->type = 0x12;
        }
        if (((SwordFlipView *)&e->spriteSettings)->flipX) {
            effect->x.HALF.HI = e->x.HALF.HI - swordSpawnOffsets[e->unk_21 * 2];
        } else {
            effect->x.HALF.HI = e->x.HALF.HI + swordSpawnOffsets[e->unk_21 * 2];
        }
        effect->y.HALF.HI = e->y.HALF.HI + swordSpawnOffsets[e->unk_21 * 2 + 1];
        effect->z.WORD = e->z.WORD;
        effect->layer = e->layer;
        RegistObjWork(6, effect);
    } else if (owner->frame & 0x20) {
        func_02085f98(data_0212ceb0[e->type].entity, 0x1c);
    }
}
