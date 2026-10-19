#include "boss/boss_02039ed4.h"
#include "global.h"

// Function names (dsd -> name), also in scratch/agentA/renames.txt:
// Boss_StartDying Boss_StartDying, Boss_CheckWallDeath Boss_CheckWallDeath, Boss_UpdateLaunchWait Boss_UpdateLaunchWait,
// Boss_StartAction3 Boss_StartAction3, Boss_UpdateContact Boss_UpdateContact, Boss_DispatchAction2 Boss_DispatchAction2,
// Boss_UpdateTarget Boss_UpdateTarget, Boss_Release Boss_Release (tail-calls func_02084788),
// Boss_SyncChildToParent Boss_SyncChildToParent, Boss_SpawnChild Boss_SpawnChild, Boss_OnAnimLoop Boss_OnAnimLoop,
// Boss_AdvanceAfterLoop Boss_AdvanceAfterLoop, Boss_RetargetTick Boss_RetargetTick

ARM void Boss_StartDying(Entity *e) {
    e->action = 4;
    e->iframes = 0xfc;
    VBD(e)->dying = 1;
    e->unk_3f = 0x11;
    e->zVelocity = 0x20000;
    e->unk_5c = 0x21ff;
    VBD(e)->dyingTimer = 0xf0;
    Boss_SetAnimation(e, 2);
    EnqueueSFX(0x2a);
}

ARM void Boss_CheckWallDeath(Entity *e) {
    int a;
    int b;
    if (VBD(e)->dying != 0) {
        return;
    }
    if (e->unk_2c & 0xe) {
        a = func_02083c74(e, 2, -6);
        b = func_02083c74(e, -2, -6);
        if (a == 0x10e || b == 0x10e) {
            Boss_StartDying(e);
            return;
        }
    } else if (e->unk_2c & 0xe0) {
        a = func_02083c74(e, 2, 6);
        b = func_02083c74(e, -2, 6);
        if (a == 0x10e || b == 0x10e) {
            Boss_StartDying(e);
            return;
        }
    }
    if (e->unk_2c & 0xe000) {
        a = func_02083c74(e, 8, 2);
        b = func_02083c74(e, 8, -2);
        if (a == 0x10e || b == 0x10e) {
            Boss_StartDying(e);
        }
        return;
    }
    if (e->unk_2c & 0xe00) {
        a = func_02083c74(e, -8, 2);
        b = func_02083c74(e, -8, -2);
        if (a == 0x10e || b == 0x10e) {
            Boss_StartDying(e);
        }
    }
}

ARM int Boss_UpdateLaunchWait(Entity *e) {
    VBL(e)->launchTimer--;
    if (VBL(e)->launchTimer == 0) {
        if (e->action == 2 && data_0212ceb0[e->type2].unk_02 != 0) {
            VBL(e)->launchTimer = 4;
        } else {
            e->action = 1;
            e->timer = 1;
            e->unk_1a = 0;
            e->iframes = 0xfc;
            e->unk_46 = 0xc;
            e->unk_3f = 0x10;
            e->unk_5c = 0x31ff;
            Boss_SetAnimation(e, 0);
            e->unk_2e = 2;
            return 0;
        }
    } else {
        if (VBL(e)->launchTimer == 0x3c) {
            e->unk_1a = 2;
        }
        if (VBL(e)->launchTimer < 0x3c && (VBL(e)->launchTimer & 1) != 0) {
            e->x.HALF.HI += data_020d1cbc[(VBL(e)->launchTimer & 6) >> 1];
        }
    }
    return 1;
}

ARM void Boss_StartAction3(Entity *e) {
    e->action = 3;
    e->unk_46 = 3;
    e->unk_3f = 0x47;
    e->unk_5c = 0x31ff;
    Boss_SetAnimation(e, 4);
    e->unk_2e = 2;
}

ARM void Boss_UpdateContact(Entity *e) {
    Entity *target;
    u8 index;
    if (e->type2 == 0) {
        func_02084700(e);
        target = func_020849c8(e);
        if (target != NULL) {
            if (e->action == 4) {
                Boss_LaunchChild(e);
            }
            func_02084ab8(e, target);
        } else {
            index = func_02084a30(e);
            data_020d1e14[index](e);
        }
    } else {
        Boss_SyncChildToParent(e);
    }
}

ARM void Boss_DispatchAction2(Entity *e) {
    data_020d1e2c[e->action](e);
}

ARM void Boss_UpdateTarget(Entity *e) {
    if (e->unk_3f == 0x14) {
        e->unk_3f = 0x13;
        e->hitbox = data_020d1db4;
        e->unk_3c &= 0x7f;
        e->unk_20 = VBT(e)->unk_7e;
        e->spriteSettings.b20 = VBT(e)->unk_7d;
        e->spriteSettings.b16 = e->spriteSettings.b20;
        e->spriteSettings.b6 = (VBT(e)->unk_7e & 0xff00) >> 8;
        e->unk_1b = 0x2c;
        e->action++;
        InitAnimationForceUpdate(e, 2);
        e->parent->spriteSettings.b0 = 1;
        InitAnimationForceUpdate(e->parent, 5);
        func_020768d8(e);
        if (e->contactedEntity->unk_08 == 8 || e->contactedEntity->unk_08 == 1) {
            e->child = data_0212ceb0[e->contactedEntity->type].entity;
        } else {
            e->child = func_02045eb4();
        }
        return;
    }
    if (e->action == 4) {
        Boss_LaunchChild(e);
    }
    if (e->contactedEntity->unk_08 == 1) {
        if ((data_0212ceb0[e->contactedEntity->type].unk_36 & 2) == 0) {
            if (e->action == 2) {
                InitAnimationForceUpdate(e, 0);
                InitAnimationForceUpdate(e->parent, 3);
            }
            e->child = e->contactedEntity;
            e->child->unk_3c &= 0x7f;
            VBT(e)->unk_78 = e->child->unk_2e;
            e->unk_5c = data_020d1dac[e->child->type];
            e->action = 4;
            e->subtimer = 0;
            VBT(e)->unk_7c = 0x2d;
        } else {
            e->child = func_02045eb4();
        }
    } else if (e->contactedEntity->unk_08 == 8) {
        e->child = data_0212ceb0[e->contactedEntity->type].entity;
    } else {
        e->child = func_02045eb4();
    }
    e->direction = GetFacingDirection(e, e->child);
}

ARM void Boss_Release(Entity *e) {
    func_02084788(e);
}

ARM void Boss_SyncChildToParent(Entity *e) {
    Entity *parent = e->parent;
    e->x.HALF.HI = parent->x.HALF.HI;
    e->y.HALF.HI = parent->y.HALF.HI + 1;
    e->z.HALF.HI = parent->z.HALF.HI - 1;
    e->spriteSettings.b30 = parent->spriteSettings.b30;
    e->spriteSettings.b14 = parent->spriteSettings.b14;
    data_020d1da4[e->action](e);
}

ARM void Boss_SpawnChild(Entity *e) {
    Entity *child;
    Tbl3 table;
    child = CreateEnemy(9);
    if (child == NULL) {
        return;
    }
    e->parent = child;
    child->parent = e;
    child->type = e->type;
    child->type2 = 1;
    VBT(e)->unk_7d = e->spriteSettings.b16;
    e->spriteSettings.b20 = data_020d1d90[e->type];
    e->spriteSettings.b16 = e->spriteSettings.b20;
    if (*((u8 *)&data_0212c7c8 + 0x8e) == 2) {
        table = *(Tbl3 *)data_020d1d8c;
        e->spriteSettings.b20 = table.v[e->type];
        e->spriteSettings.b16 = e->spriteSettings.b20;
    }
    e->unk_2e = 2;
    e->unk_3c |= 0x80;
    e->hitbox = data_020d1d9b;
    e->spriteSettings.b0 = 1;
    VBT(e)->unk_7e = e->unk_20 | (e->spriteSettings.b6 << 8);
    e->unk_20 = 0x28;
    e->spriteSettings.b6 = 3;
    e->action++;
    e->timer = 0x78;
    InitAnimationForceUpdate(e, 0);
}

ARM void Boss_OnAnimLoop(Entity *e) {
    Boss_UpdateAnimPair(e);
    if ((e->frame & 0x80) != 0) {
        InitAnimationForceUpdate(e, 0);
        InitAnimationForceUpdate(e->parent, 3);
        e->unk_28 = (Random() & 0xf0) + 1;
    }
}

ARM void Boss_AdvanceAfterLoop(Entity *e) {
    Boss_UpdateAnimPair(e);
    if ((e->frame & 0x80) != 0) {
        e->action++;
        e->timer = 8;
        e->animationState = 0;
        {
            int dir = func_02084fd0(e, e->child);
            e->direction = dir;
            e->animationState = (dir & 0xff) >> 4;
        }
        InitAnimationForceUpdate(e, e->animationState);
        InitAnimationForceUpdate(e->parent, e->animationState + 3);
    } else if (e->frame == 1) {
        e->frame = 0;
        e->unk_3c |= 0x80;
    }
}

ARM void Boss_RetargetTick(Entity *e) {
    if (--e->timer == 0) {
        e->timer = 8;
        if (func_0208de54(func_0208da4c()) == 0) {
            e->child = data_0212ceb0[*func_02093b5c()].entity;
        }
        e->direction = func_02084fd0(e, e->child);
        Boss_UpdateAnimFromDirection(e);
    }
    func_020847a0(e);
    Boss_UpdateAnimPair(e);
}
