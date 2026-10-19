#include "boss/boss_02039ed4.h"
#include "global.h"

// Function names (dsd -> name), also in scratch/agentA/renames.txt:
// nextendmoveset nextendmoveset, sleepSet sleepSet, dirSet dirSet,
// Boss_RunStateTableB Boss_RunStateTableB, em11_normal em11_normal, Boss_GenericKnockbackB Boss_GenericKnockbackB,
// em11_init em11_init, em11_wait em11_wait, em11_look em11_look,
// em11_tame em11_tame, em11_jump em11_jump, em11_land em11_land,
// em11_waitSet em11_waitSet, Boss_RunStateTableC Boss_RunStateTableC, em12_normal em12_normal

ARM void nextendmoveset(Entity *e) {
    if ((e->direction & 8) != 0) {
        if ((e->y.HALF.HI & 0xf) == 8) {
            sleepSet(e);
            return;
        }
        if ((u32)(e->y.HALF.HI & 0xf) < 8) {
            e->direction = 0x10;
        } else {
            e->direction = 0;
        }
    } else {
        if ((e->x.HALF.HI & 0xf) == 8) {
            sleepSet(e);
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

ARM void sleepSet(Entity *e) {
    e->action = 6;
    InitAnimationForceUpdate(e, 5);
    EnqueueSFX(0x30);
}

ARM void dirSet(Entity *e) {
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

ARM void em11_normal(Entity *e) {
    data_020d205c[e->action](e);
}

ARM void Boss_GenericKnockbackB(Entity *e) {
    GenericKnockback(e, data_020d2044);
}

ARM void em11_init(Entity *e) {
    e->spriteSettings.b0 = 1;
    e->unk_2e = 2;
    e->hitbox = data_020d2000;
    em11_waitSet(e);
}

ARM void em11_wait(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (--e->timer == 0) {
        e->action = 2;
        InitAnimationForceUpdate(e, 1);
    }
}

ARM void em11_look(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if ((e->frame & 0x80) != 0) {
        e->action = 3;
        InitAnimationForceUpdate(e, 2);
    }
}

ARM void em11_tame(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if ((e->frame & 0x80) != 0) {
        e->action = 4;
        e->zVelocity = 0x16000;
        e->direction = GetFacingDirection(e, EmGetAimPl());
        InitAnimationForceUpdate(e, 3);
        EnqueueSFX(0x31);
    }
}

ARM void em11_jump(Entity *e) {
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

ARM void em11_land(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if ((e->frame & 0x80) != 0) {
        em11_waitSet(e);
    }
}

ARM void em11_waitSet(Entity *e) {
    e->action = 1;
    e->timer = data_020d1ff4[Random() & 3];
    InitAnimationForceUpdate(e, 0);
}

ARM void Boss_RunStateTableC(Entity *e) {
    EnemyFunctionHandler(e, data_020d215c);
}

ARM void em12_normal(Entity *e) {
    data_020d21dc[e->action](e);
}
