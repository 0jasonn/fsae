#include "boss/boss_02039ed4.h"
#include "global.h"

// Function names (dsd -> name), also in scratch/agentA/renames.txt:
// Boss_SnapDirection Boss_SnapDirection, Boss_EnterAction6 Boss_EnterAction6, Boss_TurnTowardTarget Boss_TurnTowardTarget,
// Boss_RunStateTableB Boss_RunStateTableB, Boss_DispatchAction4 Boss_DispatchAction4, Boss_GenericKnockbackB Boss_GenericKnockbackB,
// Boss_SetupAltHitbox Boss_SetupAltHitbox, Boss_TimerThenAnim Boss_TimerThenAnim, Boss_FrameWaitThenAnim Boss_FrameWaitThenAnim,
// Boss_LaunchAtNearest Boss_LaunchAtNearest, Boss_AnimateUntilDone Boss_AnimateUntilDone, Boss_AnimFrameThenInit Boss_AnimFrameThenInit,
// Boss_ResetIdleTimer Boss_ResetIdleTimer, Boss_RunStateTableC Boss_RunStateTableC, Boss_DispatchAction5 Boss_DispatchAction5

ARM void Boss_SnapDirection(Entity *e) {
    if ((e->direction & 8) != 0) {
        if ((e->y.HALF.HI & 0xf) == 8) {
            Boss_EnterAction6(e);
            return;
        }
        if ((u32)(e->y.HALF.HI & 0xf) < 8) {
            e->direction = 0x10;
        } else {
            e->direction = 0;
        }
    } else {
        if ((e->x.HALF.HI & 0xf) == 8) {
            Boss_EnterAction6(e);
            return;
        }
        if ((u32)(e->x.HALF.HI & 0xf) < 8) {
            e->direction = 8;
        } else {
            e->direction = 0x18;
        }
    }
    e->action = 4;
    InitAnimationForceUpdate(e, (e->direction & 0xff) >> 3);
}

ARM void Boss_EnterAction6(Entity *e) {
    e->action = 6;
    InitAnimationForceUpdate(e, 5);
    EnqueueSFX(0x30);
}

ARM void Boss_TurnTowardTarget(Entity *e) {
    int r = func_02084fd0(e, VBP(e)->target);
    u8 dir = e->direction;
    if ((e->unk_2c & data_020d1eb8[dir >> 3]) != 0) {
        if (((r + 4) & 0x18) == dir) {
            if ((dir & 8) != 0) {
                if (VBP(e)->target->y.HALF.HI > e->y.HALF.HI) {
                    r = 0x10;
                } else if (VBP(e)->target->y.HALF.HI < e->y.HALF.HI) {
                    r = 0;
                } else {
                    r = Random() & 0x10;
                }
            } else {
                if (VBP(e)->target->x.HALF.HI > e->x.HALF.HI) {
                    r = 8;
                } else if (VBP(e)->target->x.HALF.HI < e->x.HALF.HI) {
                    r = 0x18;
                } else {
                    r = (u8)((Random() & 0x10) + 8);
                }
            }
        }
    }
    e->direction = (r + 4) & 0x18;
}

ARM void Boss_RunStateTableB(Entity *e) {
    EnemyFunctionHandler(e, data_020d2044);
}

ARM void Boss_DispatchAction4(Entity *e) {
    data_020d205c[e->action](e);
}

ARM void Boss_GenericKnockbackB(Entity *e) {
    GenericKnockback(e, data_020d2044);
}

ARM void Boss_SetupAltHitbox(Entity *e) {
    e->spriteSettings.b0 = 1;
    e->unk_2e = 2;
    e->hitbox = data_020d2000;
    Boss_ResetIdleTimer(e);
}

ARM void Boss_TimerThenAnim(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (--e->timer == 0) {
        e->action = 2;
        InitAnimationForceUpdate(e, 1);
    }
}

ARM void Boss_FrameWaitThenAnim(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if ((e->frame & 0x80) != 0) {
        e->action = 3;
        InitAnimationForceUpdate(e, 2);
    }
}

ARM void Boss_LaunchAtNearest(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if ((e->frame & 0x80) != 0) {
        e->action = 4;
        e->zVelocity = 0x16000;
        e->direction = GetFacingDirection(e, func_02045eb4());
        InitAnimationForceUpdate(e, 3);
        EnqueueSFX(0x31);
    }
}

ARM void Boss_AnimateUntilDone(Entity *e) {
    if ((e->frame & 0x80) == 0) {
        UpdateAnimationSingleFrame(e);
    }
    func_020847a0(e);
    if (UpdateGravity(e, 0x1200) != 0) {
        return;
    }
    e->action = 5;
    InitAnimationForceUpdate(e, 4);
}

ARM void Boss_AnimFrameThenInit(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if ((e->frame & 0x80) != 0) {
        Boss_ResetIdleTimer(e);
    }
}

ARM void Boss_ResetIdleTimer(Entity *e) {
    e->action = 1;
    e->timer = data_020d1ff4[Random() & 3];
    InitAnimationForceUpdate(e, 0);
}

ARM void Boss_RunStateTableC(Entity *e) {
    EnemyFunctionHandler(e, data_020d215c);
}

ARM void Boss_DispatchAction5(Entity *e) {
    data_020d21dc[e->action](e);
}
