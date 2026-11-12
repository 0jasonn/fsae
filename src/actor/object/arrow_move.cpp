#include "engine/functions.h"
#include "global.h"
#include "actor/object/arrow_move.h"

// Arrow (module arrow): arrow_move, the arrow while it is held (charging) and while it flies.

// Arrow-only fields that Entity does not name.
typedef struct Vars_Arrow {
    u8 unk_00[0x64];
    s32 hitOffsetX; // 0x64: low half is the x offset of the wall-hit probe
    s32 hitOffsetY; // 0x68: low half is the y offset of the wall-hit probe
    u8 lifetime;    // 0x6c: frames left; the arrow blinks for the last 0x18
} Vars_Arrow;

// Arrow move. While held (subtimer set) it follows its owner, charges with the tame counter and fires a copy once
// the owner's animation frame flag is set; in flight it moves, sticks into walls and bounces off shields.
void arrow_move(Entity *e) {
    Entity *owner = playerWork[e->type].entity;
    u8 tame;

    if (e->subtimer != 0) {
        UpdateAnimationSingleFrame(e);
        if (VARS(Vars_Arrow, e)->lifetime < 0x18) {
            e->spriteSettings.b0 ^= 1;
        }
        if (--VARS(Vars_Arrow, e)->lifetime == 0) {
            func_020841b0(e);
            PutObjWork(e);
            return;
        }
        if (func_02089e34(e, 4, e->x.HALF.HI + (s16)VARS(Vars_Arrow, e)->hitOffsetX,
                          e->y.HALF.HI + (s16)VARS(Vars_Arrow, e)->hitOffsetY) != 0) {
            if (e->attackDamage > 3) {
                return;
            }
            func_020841b0(e);
            PutObjWork(e);
            return;
        }
        MoveDir(e);
        e->timer++;
        if (e->attackDamage > 3 && (e->timer & 7) == 0) {
            EffectSet(e, 0x14, 0);
        }
        if (e->type2 == 0) {
            func_02086168(e);
        }
        PlWeaponFireCheck(e);
        {
            u16 *cellBase = (u16 *)GetBgBuffAdrs(e->layer);
            s32 cell = ((e->x.HALF.HI - mapState.originX) >> 4) | (((e->y.HALF.HI - mapState.originY) >> 4) << 6);
            u16 index = (u16)(cellBase[cell + 2] & 0x7ff);
            u16 value = *(u16 *)((u8 *)cellBase + (index << 1) + 0x5004);
            if (func_020899bc(value, data_021180a8) == 0 && func_02083cdc(e) != 0x47 &&
                func_02085890(e, data_0211857c, e->x.HALF.HI, e->y.HALF.HI) != 0) {
                e->action++;
                if (e->attackDamage > 3) {
                    e->unk_23 -= 0xd;
                }
                e->timer = 0x1e;
                InitAnimationForceUpdate(e, e->unk_23 + 2);
                func_020841b0(e);
                e->speed = e->statusFlags = 0;
                e->x.WORD = e->x.WORD > 0 ? e->x.WORD : 0;
                e->y.WORD = e->y.WORD > 0 ? e->y.WORD : 0;
                EnqueueSFX(0x90);
            }
        }
        if (e->contactFlags == 0) {
            return;
        }
        func_020841b0(e);
        if ((e->contactFlags & 0x3f) != 0 && (e->contactFlags & 0x3f) <= 0x15) {
            e->spriteSettings.b0 = 1;
            e->action = 3;
            e->direction ^= 0x10;
            e->speed = 0x100;
            e->zVelocity = 0x8000;
            InitAnimationForceUpdate(e, 8);
            e->statusFlags = 0;
            return;
        }
        e->action++;
        e->timer = 1;
        e->spriteSettings.b0 = 0;
    } else {
        tame = playerWork[e->type].tameState;
        if (tame != 0) {
            if (tame < 0x5a) {
                playerWork[e->type].tameState = tame + 1;
            } else {
                e->attackDamage = 6;
            }
        }
        if (e->attackDamage > 3) {
            if ((frameCounter & 7) < 4) {
                e->spriteSettings.b16 = 0;
            } else {
                e->spriteSettings.b16 = 3;
            }
        }
        e->unk_21 = owner->unk_21;
        if (owner->frame & 1) {
            u8 inUse = playerWork[e->type].inUse;
            if (inUse != 0 && !(inUse & 8)) {
                Entity *shot = GetObjWork();
                if (shot != NULL) {
                    shot->objId = 3;
                    shot->objKind = 8;
                    shot->type = e->type;
                    shot->subtimer = 1;
                    shot->attackDamage = e->attackDamage;
                    RegistObjWork(2, shot);
                }
            }
        }
        if (playerWork[e->type].inUse == 0 || (playerWork[e->type].inUse & 8)) {
            playerWork[e->type].weapon = NULL;
            playerWork[e->type].tameState = 0;
            func_020841b0(e);
            PutObjWork(e);
        }
    }
}
