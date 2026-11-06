#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"
#include "actor/object/sword_move.h"

// Sword actor (module sword). Address -> name:
//   0x0207b190 sword_move (original name): per-frame update of the sword: removal, hit sounds, wave spawn

void sword_move(Entity *e) {
    Entity *owner = playerWork[e->type].entity;

    if (playerWork[e->type].weapon != e) {
        func_020841b0(e);
        zFree((void *)e->hitbox);
        PutObjWork(e);
        return;
    }
    if (playerWork[e->type].inUse == 0) {
        playerWork[e->type].weapon = NULL;
        playerWork[e->type].actionFlags = 0;
        func_020841b0(e);
        zFree((void *)e->hitbox);
        PutObjWork(e);
        return;
    }
    if (playerWork[e->type].inUse & 0x80) {
        func_02085f98(owner, 0x14);
    }
    if (playerWork[e->type].actionFlags != 0) {
        e->unk_40 = 0xc;
        if (playerWork[e->type].actionFlags & 0x20) {
            e->spriteSettings.b16 ^= 3;
        }
        if (playerWork[e->type].actionFlags & 0x40) {
            e->attackDamage = ((SwordLevelView *)&playerWork[e->type].unk_3e)->level * 2 + 8;
            e->unk_40 = 8;
        }
    }
    sword_plsync(e, owner);
    PlWeaponFireCheck(e);
    swordEvent(e);
    if (playerWork[e->type].actionFlags == 0) {
        Entity *effect;

        if (((SwordLevelView *)&playerWork[e->type].unk_3e)->level == 0) {
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
        if (((SwordLevelView *)&playerWork[e->type].unk_3e)->level == 1) {
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
        func_02085f98(playerWork[e->type].entity, 0x1c);
    }
}
