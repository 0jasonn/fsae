#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"
#include "actor/object/shield.h"

// Shield actor (module shield). Address -> name:
//   0x02076cd4 shieldMove (original name): follows its owner, takes over the damage fields and copies the owner animation

void shieldMove(Entity *e) {
    Vars_Shield *v = VARS(Vars_Shield, e);
    Entity *owner = playerWork[e->type].entity;

    if (owner->iframes == 0 || owner->iframes == 0x81) {
        owner->iframes = e->iframes;
        owner->baseDirection = e->baseDirection;
        owner->unk_42 = e->unk_42;
        e->unk_42 = 0;
        e->baseDirection = 0;
        e->iframes = 0;
    }
    if (playerWork[e->type].unk_03 != 0 && e == playerWork[e->type].weapon) {
        if (playerWork[e->type].unk_03 & 0x80) {
            e->hitbox = shieldHitboxTable[owner->animationState >> 1];
            playerWork[e->type].unk_03 &= 0x7f;
            e->statusFlags = (owner->statusFlags + 1) | 0x20;
            func_02084320(e);
        } else if ((e->contactFlags & 0x80) && e->contactedEntity->unk_1b != 0x2e) {
            if (v->hitSoundTimer == 0) {
                func_02085f98(owner, 0x1e);
                v->hitSoundTimer = 8;
            }
            if ((e->contactFlags & 0x7f) == 0) {
                if (playerWork[e->contactedEntity->type].hitFlags != 0) {
                    playerWork[e->contactedEntity->type].hitFlags = 0;
                    e->contactedEntity->iframes = 0;
                }
            }
        }
    } else {
        e->timer = 0;
        playerWork[e->type].unk_03 = 0;
        e->spriteSettings.b16 = 3;
        func_020841b0(e);
        e->statusFlags = 0;
        if (playerWork[e->type].weapon == e) {
            playerWork[e->type].weapon = NULL;
        }
        PutObjWork(e);
        return;
    }
    if (owner->unk_1b == 0) {
        if (owner->unk_21 >= 0xd0 || owner->unk_21 < 0xa9) {
            e->unk_21 = 0xff;
        } else {
            SPRITE_FLIP(e)->flipX = SPRITE_FLIP(owner)->flipX;
            SPRITE_FLIP(e)->flipY = SPRITE_FLIP(owner)->flipY;
            e->unk_21 = owner->unk_21 - 0xa9;
            e->frame = owner->frame;
            e->unk_2f = owner->unk_2f;
        }
    } else {
        e->unk_21 = 0xff;
    }
}
