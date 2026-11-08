#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"
#include "actor/object/tama0f.h"
#include "actor/object/tama_decls.h"

extern "C" void tama0f_init(Entity *e);

// tama0f_init, 0x0207d3cc. Initialises a tama0f projectile for its type2 variant (0 fireball, 1 homing shot, 2 wait,
// 3 scatter, 4 hidden storm) and sets the common state.
void tama0f_init(Entity *e) {
    u8 parentType;
    switch (e->type2) {
    case 0:
        e->spriteSettings.b16 = e->timer + 7;
        e->spriteSettings.b20 = e->spriteSettings.b16;
        e->speed = 0x100;
        e->direction = func_02086078(e, playerWork[e->timer].entity);
        e->subtimer = 3;
        parentType = e->parent->type;
        VARS(Vars_Tama0f, e)->fireTimer = parentType;
        VARS(Vars_Tama0f, e)->unk_74 = 0;
        if (gameState.level == 1) {
            if (parentType == 4) {
                VARS(Vars_Tama0f, e)->fireTimer = 2;
            }
        } else if (parentType == 3) {
            VARS(Vars_Tama0f, e)->fireTimer = 4;
        }
        if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) != 0) {
            VARS(Vars_Tama0f, e)->fireTimer = VARS(Vars_Tama0f, e)->fireTimer + gameState.playerCount;
        }
        EnqueueSFX(0x9f);
        e->unk_2e = 3;
        e->unk_5e.b2 = 1;
        e->spriteSettings.b4 = 0;
        if ((Random() & 3) == 0 && e->parent != 0) {
            TamaTelopIds listA = data_020dcb60;
            TamaTelopIds listB = data_020dcb68;
            u16 telopId;
            if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) != 0) {
                telopId = listA.ids[VARS(Vars_TamaParent, e->parent)->itemIndex];
            } else {
                telopId = listB.ids[VARS(Vars_TamaParent, e->parent)->itemIndex];
            }
            TelopRequest(telopId);
            VARS(Vars_TamaParent, e->parent)->itemIndex = (VARS(Vars_TamaParent, e->parent)->itemIndex + 1) % 3;
        }
        break;
    case 1:
        e->direction = func_02086078(e, playerWork[e->timer].entity);
        e->subtimer = 0x14;
        VARS(Vars_Tama0f, e)->fireTimer = 0x12c;
        e->speed = 0xc0;
        e->spriteSettings.b16 = 0xb;
        e->spriteSettings.b20 = e->spriteSettings.b16;
        EnqueueSFX(0xba);
        break;
    case 2:
        if (func_02083d28(e) == 0) {
            e->subtimer = 0x3c;
            e->spriteSettings.b16 = 0xb;
            e->spriteSettings.b20 = e->spriteSettings.b16;
            e->statusFlags = e->statusFlags & 0x7f;
        } else {
            PutObjWork(e);
            return;
        }
        break;
    case 3:
        e->spriteSettings.b16 = 0xb;
        e->spriteSettings.b20 = e->spriteSettings.b16;
        e->direction = Random() & 0x1f;
        e->speed = Random() & 0x1ff;
        e->zVelocity = (Random() & 0x3ffff) | 0x10000;
        e->unk_2e = 1;
        e->spriteSettings.b4 = 1;
        EnqueueSFX(0xbb);
        break;
    case 4:
        e->subtimer = 0x2d;
        e->speed = 0x100;
        e->unk_2e = 1;
        e->spriteSettings.b16 = 0xb;
        e->spriteSettings.b20 = e->spriteSettings.b16;
        e->spriteSettings.b4 = 1;
        e->statusFlags = e->statusFlags & 0x7f;
        break;
    default:
        break;
    }
    InitAnimationForceUpdate(e, data_020dcb1b[e->type2]);
    e->action = e->type2 + 1;
    e->spriteSettings.b0 = 1;
    e->hitbox = data_02117b90[e->type2];
    e->layer = 0x4000;
    e->unk_20 = 0x80;
    e->z.WORD = -1;
    e->spriteSettings.b30 = 1;
    e->spriteSettings.b14 = e->spriteSettings.b30;
}
