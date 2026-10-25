#include "engine/functions.h"
#include "global.h"
#include "enemy/em22.h"
#include "enemy/em22_2.h"

// Functions in this file: em22_damage (0x0203f7ac), em22_init (0x0203f850), em22_aim (0x0203f8b0),
// em22_move (0x0203f924), dmgmgr (0x0203f99c), spdmgr (0x0203fa1c).

ARM void em22_damage(Entity *e) {
    if ((u8)((e->contactFlags & 0x7f) - 4) <= 0x1e) {
        if (e->contactFlags != 0x95 && e->contactFlags != 0x94) {
            s32 stage;
            e->speed = 0x40;
            if (VARS(Vars_em22, e)->damageStage < 3) {
                stage = VARS(Vars_em22, e)->damageStage + 1;
                if ((u8)stage == 3) {
                    e->poseId = 0x35;
                }
                VARS(Vars_em22, e)->damageTimer = 0x1e;
                VARS(Vars_em22, e)->damageStage = stage;
                if (!KnifeApp_isWirelessMode(KnifeApp_getInstance())) {
                    VARS(Vars_em22, e)->damageTimer += 0x14;
                }
                e->animationState = VARS(Vars_em22, e)->damageStage;
                InitAnimationForceUpdate(e, VARS(Vars_em22, e)->damageStage);
                EnqueueSFX(0x5b);
            }
        }
    }
    GenericKnockback(e, em22_stateTable);
}

ARM void em22_init(Entity *e) {
    e->action = 1;
    e->timer = 0x1e;
    e->unk_2e = 5;
    e->spriteSettings.b0 = 1;
    e->spriteSettings.b4 = 2;
    e->unk_5e.b2 = 1;
    e->hitbox = em22_hitbox;
    e->animationState = 0;
    InitAnimationForceUpdate(e, 0);
}

ARM void em22_aim(Entity *e) {
    Entity *target;
    u8 timer;
    if (e->timer != 0) {
        e->timer--;
        return;
    }
    target = func_02084f98(e, 0x60, 0x50);
    if (target == NULL) {
        return;
    }
    VARS(Vars_em22, e)->aimTarget = target;
    e->direction = GetFacingDirection(e, target);
    e->action = 2;
    timer = em22_aimTimerTable[Random() & 7];
    e->speed = 0x40;
    VARS(Vars_em22, e)->speedTimer = 8;
    e->timer = timer;
}

ARM void em22_move(Entity *e) {
    if ((frameCounter & 7) == 0) {
        func_02086200(e, func_02084fd0(e, VARS(Vars_em22, e)->aimTarget));
    }
    spdmgr(e);
    func_020847a0(e);
    if (--e->timer == 0) {
        e->action = 1;
        e->timer = em22_moveTimerTable[Random() & 7];
    }
}

ARM void dmgmgr(Entity *e) {
    s32 anim;
    if (VARS(Vars_em22, e)->damageTimer == 0) {
        return;
    }
    if (--VARS(Vars_em22, e)->damageTimer != 0) {
        return;
    }
    if (--VARS(Vars_em22, e)->damageStage != 0) {
        VARS(Vars_em22, e)->damageTimer = 0x1e;
        if (!KnifeApp_isWirelessMode(KnifeApp_getInstance())) {
            VARS(Vars_em22, e)->damageTimer += 0x14;
        }
    }
    anim = em22_dmgAnimTable[VARS(Vars_em22, e)->damageStage];
    e->poseId = 0x34;
    e->animationState = anim;
    InitAnimationForceUpdate(e, anim);
}

ARM void spdmgr(Entity *e) {
    if (VARS(Vars_em22, e)->speedTimer != 0) {
        VARS(Vars_em22, e)->speedTimer--;
        return;
    }
    VARS(Vars_em22, e)->speedTimer = 8;
    if (e->speed < 0x200) {
        e->speed += 0x20;
    }
}
