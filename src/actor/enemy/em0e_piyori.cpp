#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"
#include "actor/enemy/em0e_units.h"
#include "actor/enemy/em0e.h"

// Actor em0e, type2_piyori (0x0202d290, between em0e_3.cpp and em0e_4.cpp).
// Needs the Entity change spriteSettings b8:6 -> affineMode:2 + b10:4 (local copy in wip/O1/entity_affine.h).

// The first four bytes of em0e_template are the s8 x offsets of the dizzy shake (read as s8 here).
extern const u32 em0e_template[];
extern u16 em0e_scrollTable[];
extern u16 scrollArgs[3];

// Dizzy state of the type 2 group: while the part is carried (partFlags set) it follows hippariCheck and is
// released when its two pieces are pulled unk_71 apart; otherwise it shakes for the last 0x3c frames of the timeout
// and then returns to the previous action. The pieces are scaled by the pull distance; when released, both pulling
// players are freed.
void type2_piyori(Entity *e) {
    Vars_Em0e *vars = VARS(Vars_Em0e, e);
    s16 offset;
    u32 result;
    PlayerData *player;

    if (e->animationState == 1) {
        UpdateAnimationSingleFrame(e);
        result = func_02086044(e, 0x2000);
        if (result >= 2) {
            return;
        }
        if (result == 0) {
            e->animationState = 2;
            vars->body0->spriteSettings.b0 = 1;
            vars->motiage1->spriteSettings.b0 = 1;
        }
        EnqueueSFX(0x54);
        return;
    }
    if ((e->frame & 1) == 0) {
        InitAnimationForceUpdate(e, 2);
        func_02085cf8(e);
        e->spriteSettings.affineMode |= 2;
    }
    e->unk_2e = 6;
    if (vars->partFlags != 0) {
        hippariCheck(e);
        offset = vars->motiage1->x.HALF.HI - vars->body0->x.HALF.HI;
        if (offset != 0) {
            e->unk_2e = 0;
        }
        if (vars->unk_71 <= offset) {
            e->health = 0;
            EnqueueSFX(0x22e);
        }
    } else {
        vars->timeout--;
        if (vars->timeout == 0) {
            e->action--;
            e->timer = 1;
            e->attackKnockback = 0xc;
            EnqueueSFX(0x96);
        } else if (vars->timeout <= 0x3c) {
            e->x.HALF.HI += ((const s8 *)em0e_template)[vars->timeout & 3];
        }
    }
    if (e->health != 0) {
        offset = vars->motiage1->x.HALF.HI - vars->body0->x.HALF.HI;
        vars->pieceOffset = offset;
        if (offset != 0) {
            e->child->spriteSettings.b0 = 1;
            e->timer = offset;
        } else {
            e->child->spriteSettings.b0 = 0;
        }
        scrollArgs[0] = em0e_scrollTable[offset * 2];
        scrollArgs[1] = em0e_scrollTable[offset * 2 + 1];
        scrollArgs[2] = 0;
        ObjAffineSet2((KnifeObjAffineSrcData *)scrollArgs, e);
        if ((vars->partFlags & 0xc) == 0) {
            func_02089524(vars->body0);
        }
        if ((vars->partFlags & 0xc0) == 0) {
            func_02089524(vars->motiage1);
        }
    } else {
        player = &playerWork[vars->partFlags & 3];
        player->specialState = 0;
        player->entity->baseDirection = 0x18;
        player->entity->unk_42 = 8;
        player = &playerWork[(vars->partFlags >> 4) & 3];
        player->specialState = 0;
        player->entity->baseDirection = 8;
        player->entity->unk_42 = 8;
    }
}
