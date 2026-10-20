#include "engine/functions.h"
#include "global.h"
#include "object/tama11.h"

// tama11 / Throw module, 0x02080008 to 0x02080320 (tama11_throw_init, throw_move and throw_throw are in other files).
//   tama11_move1 (0x02080008): the flying object. Counts down expireTimer, then on contact steps its subtimer and
//     either re-rolls the sprite (phase 1) or switches to action 1 (phase 2), then plays SFX 0xb4 and runs fiveMove.
//   prtDamage (0x020801a0): hits the parent with damage 0x14 (or 5 for type 0) and drops a rupee.
//   fiveMove (0x02080238): shared per-frame update for the throw family, with the five-frame timer.
//   Throw (0x020802e4): dispatches on subAction through Throw_stateTable unless the game is paused, then runs func_020857c8.

// tama11_move1 (0x02080008)
ARM void tama11_move1(Entity *e) {
    if (VARS(Tama11Vars, e)->expireTimer != 0) {
        VARS(Tama11Vars, e)->expireTimer--;
        if (VARS(Tama11Vars, e)->expireTimer == 0) {
            e->statusFlags |= 0x80;
        }
    }
    if (e->contactFlags & 0x80) {
        if (e->spriteSettings.b16 - 7 == e->contactedEntity->type && (u8)(e->contactFlags - 0x84) <= 0x87) {
            e->subtimer++;
            VARS(Tama11Vars, e)->frameCounter++;
            if (VARS(Tama11Vars, e)->phaseLength > e->subtimer) {
                e->iframes = 0xf0;
                u32 roll = Random() % (data_0212c7c8.unk_0 - 1);
                e->spriteSettings.b16 = tama11_spriteTable[e->spriteSettings.b16][roll];
                e->spriteSettings.b20 = e->spriteSettings.b16;
                if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) || Knife_Single_SinglePlay_GetInstance()[1] != 0) {
                    e->direction = e->baseDirection;
                } else {
                    e->direction = func_02086078(e, *(Entity **)(tama11_objTemplates + e->spriteSettings.b20 * 0x94));
                }
            } else {
                e->action = 1;
                e->type2 |= 2;
                if (KnifeApp_isWirelessMode(KnifeApp_getInstance())) {
                    e->direction = e->baseDirection;
                } else {
                    e->direction = func_02086078(e, e->parent);
                }
            }
            EnqueueSFX(0xb4);
        }
    }
    fiveMove(e);
}

// prtDamage (0x020801a0)
ARM void prtDamage(Entity *e) {
    u8 damage;

    e->parent->contactFlags = 0xff;
    e->parent->iframes = 0x3c;
    damage = e->type != 0 ? 0x14 : 5;
    if (e->parent->health > damage) {
        e->parent->health -= damage;
    } else {
        e->parent->health = 0;
    }
    if (e->type == 0) {
        Entity *parent = e->parent;
        u8 dropKind = parent->type2;

        parent->type2 = dropKind + 1;
        EmBossDropRupee(e, dropKind, 0, 0);
    } else {
        EmBossDropRupee(e, VARS(Tama11Vars, e)->frameCounter, 0, 0);
    }
    func_02085f98(e, 0x2d);
}

// fiveMove (0x02080238)
ARM void fiveMove(Entity *e) {
    VARS(Tama11Vars, e)->fiveMoveTimer--;
    if (e->type2 & 1) {
        if (VARS(Tama11Vars, e)->fiveMoveTimer == 0) {
            Entity *disp;

            VARS(Tama11Vars, e)->fiveMoveTimer = 5;
            disp = ((Entity * (*)(Entity *, u8, u8, u8)) SetDisp)(e, 0, 1, 0);
            if (disp != NULL) {
                disp->unk_23 = 1;
            }
        }
    }
    UpdateAnimationSingleFrame(e);
    func_0208b658(e);
    if (e->type2 & 2) {
        if (func_02083ed8(e, e->parent)) {
            prtDamage(e);
            PutObjWork(e);
            return;
        }
    }
    if (e->wallFlags != 0) {
        PutObjWork(e);
    }
}

// Throw (0x020802e4)
ARM void Throw(Entity *e) {
    if (data_0212c4b8 == 0) {
        Throw_stateTable[e->subAction](e);
    }
    func_020857c8(e);
}
