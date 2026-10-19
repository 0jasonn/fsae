#include "boss/boss_02039074.h"
#include "global.h"

// Function names (dsd -> name), also in scratch/agentA/renames.txt:
// Boss_FallAfterDelay Boss_FallAfterDelay, Boss_IdleCycle Boss_IdleCycle, Boss_ShootAttack Boss_ShootAttack,
// Boss_RandomizeDirection Boss_RandomizeDirection, Boss_JumpRecover Boss_JumpRecover, Boss_Update Boss_Update,
// Boss_UpdateStateFlags Boss_UpdateStateFlags, Boss_DispatchAction Boss_DispatchAction, Boss_Knockback Boss_Knockback,
// Boss_InitIdle Boss_InitIdle, Boss_AnimateHeightFrame Boss_AnimateHeightFrame, Boss_HandleEnemyState Boss_HandleEnemyState,
// Boss_DispatchAltAction Boss_DispatchAltAction, Boss_CheckHitReaction Boss_CheckHitReaction, Boss_Init Boss_Init,
// Boss_StartWait Boss_StartWait, Boss_RandomAction Boss_RandomAction, Boss_LaunchAtPlayer Boss_LaunchAtPlayer,
// Boss_FallToLanding Boss_FallToLanding, Boss_ChooseAfterLanding Boss_ChooseAfterLanding, Boss_ResumeIdle Boss_ResumeIdle,
// Boss_WaitThenAdvance Boss_WaitThenAdvance, Boss_InvulnerableFrames Boss_InvulnerableFrames, Boss_SplitIntoPieces Boss_SplitIntoPieces,
// Boss_UpdateHitStates Boss_UpdateHitStates, Boss_DyingUpdate Boss_DyingUpdate, Boss_HandleContact Boss_HandleContact,
// Boss_Destroy Boss_Destroy, Boss_InitHitStun Boss_InitHitStun, Boss_FloatAndTurn Boss_FloatAndTurn,
// Boss_UpdateSubAction Boss_UpdateSubAction, Boss_InitMirrorPlayer Boss_InitMirrorPlayer, Boss_SyncMirrorAnim Boss_SyncMirrorAnim,
// Boss_UpdatePose Boss_UpdatePose, Boss_ClearMotion Boss_ClearMotion, Boss_UpdateGroundContact Boss_UpdateGroundContact,
// Boss_Dive Boss_Dive, Boss_TickFlash Boss_TickFlash, Boss_Explode Boss_Explode,
// Boss_SetAnimation Boss_SetAnimation (nonmatching, see scratch/agentA/nonmatching)

ARM void Boss_FallAfterDelay(Entity *e) {
    if (e->timer != 0) {
        e->timer--;
        return;
    }
    if (UpdateGravity(e, 0x28000) != 0) {
        return;
    }
    e->action = 3;
    e->subtimer = 0x10;
    InitAnimationForceUpdate(e, e->animationState + 0xa);
    EnqueueSFX(0x5e);
}

ARM void Boss_IdleCycle(Entity *e) {
    if (e->subtimer != 0) {
        e->subtimer--;
        if (e->subtimer == 0) {
            e->action = 4;
            e->timer = 0x20;
            e->subtimer = 0;
            e->unk_3f = 6;
            InitAnimationForceUpdate(e, 0xc);
            return;
        }
    }
    if (--e->timer == 0) {
        e->timer = (Random() & 0x1c) + 0x1e;
        Boss_RandomizeDirection(e);
    }
    func_020847a0(e);
    UpdateAnimationSingleFrame(e);
}

ARM void Boss_ShootAttack(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (e->frame == 1) {
        if (e->child != NULL) {
            return;
        }
        e->child = func_02084f98(e, e->timer, e->timer);
        e->subtimer++;
        if ((e->subtimer & 3) == 0) {
            e->timer += 0x20;
        }
        return;
    }
    if (e->frame == 2) {
        e->frame = 0;
        Entity *projectile = CreateProjectile(0);
        if (projectile != NULL) {
            projectile->direction = Random() & 0x1f;
            if (e->child != NULL) {
                projectile->direction = GetFacingDirection(e, e->child);
            } else {
                projectile->direction = Random() & 0x1f;
            }
            if (e->unk_09 != 5) {
                projectile->type = 1;
            }
            CopyPosition(e, projectile);
            EnqueueSFX(0xc);
        }
        e->child = NULL;
        return;
    }
    if ((e->frame & 0x80) == 0) {
        return;
    }
    e->action = 1;
    e->timer = 1;
    e->subtimer = (Random() & 0x7f) + 0x40;
    e->animationState = 0;
    e->unk_3f = 9;
    InitAnimationForceUpdate(e, 0);
}

ARM void Boss_RandomizeDirection(Entity *e) {
    u8 direction = Random() & 0x1f;
    e->direction = direction;
    u8 newAnim = func_02045a8c(direction);
    if (newAnim == 0xff || newAnim == e->animationState) {
        return;
    }
    e->animationState = newAnim;
    InitAnimationForceUpdate(e, newAnim);
}

ARM void Boss_JumpRecover(Entity *e) {
    switch (VB(e)->jumpPhase) {
    case 0:
        if (UpdateGravity(e, 0x20000) != 0) {
            return;
        }
        e->unk_43 = 0;
        VB(e)->jumpPhase++;
        VB(e)->jumpTimer = 0x1e0;
        e->unk_3c |= 0x80;
        e->unk_3f = 0x44;
        InitAnimationForceUpdate(e, 2);
        EnqueueSFX(0x16);
        break;
    case 1:
        UpdateAnimationSingleFrame(e);
        VB(e)->jumpTimer--;
        if (VB(e)->jumpTimer == 0) {
            VB(e)->jumpPhase++;
            InitAnimationForceUpdate(e, 3);
            break;
        }
        if (VB(e)->jumpTimer < 0x3c) {
            e->x.HALF.HI += data_020d1998[VB(e)->jumpTimer & 3];
        }
        break;
    case 2:
        UpdateAnimationSingleFrame(e);
        if ((e->frame & 0x80) == 0) {
            break;
        }
        VB(e)->jumpPhase = 0;
        e->action = 1;
        e->timer = 1;
        e->subtimer = 0x10;
        e->speed = 0x80;
        e->animationState = 0;
        e->unk_3f = 6;
        e->health = VB(e)->healthBackup;
        InitAnimationForceUpdate(e, 0);
        break;
    }
}

ARM void Boss_Update(Entity *e) {
    if (data_0212c540[1] > 1) {
        func_02084700(e);
    }
    int hitResult = func_020849c8(e);
    if (hitResult != 0) {
        func_02084ab8(e, hitResult);
    } else {
        data_020d1a64[func_02084a30(e)](e);
    }
}

ARM void Boss_UpdateStateFlags(Entity *e) {
    func_02084700(e);
    data_020d1b94[func_02084a30(e)](e);
    func_0208ae30(e);
    e->spriteSettings.b30 = 1;
    e->spriteSettings.b14 = 1;
}

ARM void Boss_DispatchAction(Entity *e) {
    data_020d1b84[e->action](e);
}

ARM void Boss_Knockback(Entity *e) {
    GenericKnockback(e, data_020d1b94);
}

ARM void Boss_InitIdle(Entity *e) {
    e->spriteSettings.b0 = 1;
    e->unk_2e = 0;
    e->hitbox = data_020d1b8c;
    e->action++;
    e->direction = Random() & 0x1f;
    InitAnimationForceUpdate(e, 0);
}

ARM void Boss_AnimateHeightFrame(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (e->frame & 0x80) {
        e->direction = Random() & 0x1f;
        InitAnimationForceUpdate(e, 0);
    } else {
        func_020847f8(e);
    }
    e->z.HALF.HI = data_020d1b7c[e->frame];
}

ARM void Boss_HandleEnemyState(Entity *e) {
    EnemyFunctionHandler(e, data_020d1c20);
}

ARM void Boss_DispatchAltAction(Entity *e) {
    data_020d1c7c[e->action](e);
}

ARM void Boss_CheckHitReaction(Entity *e) {
    if (e->health != 0 && VB(e)->lastHealth != e->health) {
        e->action = 9;
        return;
    }
    GenericKnockback(e, data_020d1c20);
}

ARM void Boss_Init(Entity *e) {
    e->spriteSettings.b0 = 1;
    e->unk_2e = 2;
    e->hitbox = data_020d1bcc;
    VB(e)->lastHealth = e->health;
    InitAnimationForceUpdate(e, 0);
    e->action++;
    e->child = data_0212ceb0[0].entity;
    VB(e)->target = func_02045eb4();
    e->direction = GetFacingDirection(e, VB(e)->target);
}

ARM void Boss_StartWait(Entity *e) {
    e->action++;
    e->timer = (Random() & 0x30) + 0x20;
    InitAnimationForceUpdate(e, 0);
}

ARM void Boss_RandomAction(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (--e->timer != 0) {
        return;
    }
    switch (data_020d1bd4[Random() & 7]) {
    case 0:
        e->timer = (Random() & 0x30) + 0x20;
        return;
    case 1:
        e->action++;
        InitAnimationForceUpdate(e, 1);
        return;
    default:
        e->action = 6;
        InitAnimationForceUpdate(e, 4);
        return;
    }
}

ARM void Boss_LaunchAtPlayer(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if ((e->frame & 0x80) == 0) {
        return;
    }
    e->action++;
    e->zVelocity = 0x12000;
    e->z.HALF.HI = -8;
    if (func_0208de54(func_0208da4c()) == 0) {
        u8 playerIndex = *func_02093b5c();
        VB(e)->target = data_0212ceb0[playerIndex].entity;
    }
    e->direction = func_02084fd0(e, VB(e)->target);
    InitAnimationForceUpdate(e, 2);
    EnqueueSFX(0x31);
}

ARM void Boss_FallToLanding(Entity *e) {
    func_020847a0(e);
    UpdateAnimationSingleFrame(e);
    if (UpdateGravity(e, 0x1800) != 0) {
        return;
    }
    e->action++;
    InitAnimationForceUpdate(e, 3);
}

ARM void Boss_ChooseAfterLanding(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if ((e->frame & 0x80) == 0) {
        return;
    }
    if (Random() & 1) {
        e->action = 1;
        return;
    }
    e->action = 3;
    InitAnimationForceUpdate(e, 1);
}

ARM void Boss_ResumeIdle(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (e->frame == 1) {
        e->frame = 0;
        e->unk_3c &= 0x7f;
        return;
    }
    if ((e->frame & 0x80) == 0) {
        return;
    }
    e->action++;
    e->timer = (Random() & 0x70) + 0x1e;
    e->spriteSettings.b0 = 0;
}

ARM void Boss_WaitThenAdvance(Entity *e) {
    if (--e->timer != 0) {
        return;
    }
    e->action++;
    e->spriteSettings.b0 = 1;
    InitAnimationForceUpdate(e, 5);
}

ARM void Boss_InvulnerableFrames(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (e->frame == 1) {
        e->frame = 0;
        e->unk_3c |= 0x80;
        return;
    }
    if ((e->frame & 0x80) == 0) {
        return;
    }
    e->action = 1;
    InitAnimationForceUpdate(e, 0);
}

ARM void Boss_SplitIntoPieces(Entity *e) {
    s8 count = 0;
    Entity *pieceA = CreateEnemy(3);
    if (pieceA != NULL) {
        pieceA->z.HALF.HI = 0;
        pieceA->iframes = 0xf0;
        count++;
    }
    Entity *pieceB = CreateEnemy(3);
    if (pieceB != NULL) {
        pieceB->z.HALF.HI = 0;
        pieceB->iframes = 0xf0;
        count++;
    }
    func_02045c20(e, pieceA, pieceB);
    if (count == 2) {
        pieceA->parent = pieceB;
        pieceA->type2 = 1;
        pieceB->parent = pieceA;
        pieceB->type2 = 1;
    }
    if (e->unk_60 != NULL) {
        VARS(Vars_Target, e->unk_60)->pieceCount += (u16)count;
    }
    Entity *fx = CreateFx(0xf, 2, 0);
    if (fx != NULL) {
        CopyPosition(e, fx);
    }
    DeleteEntity(e);
}

ARM void Boss_UpdateHitStates(Entity *e) {
    EnemyFunctionHandler(e, data_020d1d40);
}

ARM void Boss_DyingUpdate(Entity *e) {
    data_020d1d58[e->action](e);
    if (VB(e)->dyingTimer == 0) {
        return;
    }
    VB(e)->dyingTimer--;
    if (VB(e)->dyingTimer == 0) {
        Boss_Explode(e);
        return;
    }
    if (VB(e)->dyingTimer >= 0x3c) {
        return;
    }
    if ((VB(e)->dyingTimer & 1) == 0) {
        return;
    }
    if (e->spriteSettings.b16 == e->spriteSettings.b20) {
        e->spriteSettings.b16 = 0xe;
    } else {
        e->spriteSettings.b16 = e->spriteSettings.b20;
    }
}

ARM void Boss_HandleContact(Entity *e) {
    switch (e->contactFlags & 0x7f) {
    case 0x16:
        Boss_Explode(e);
        return;
    case 1:
    case 2:
    case 3: {
        u8 animOffset = e->animationState - 4;
        if (animOffset < 2) {
            return;
        }
        u8 tableIndex = ((e->unk_3e + 4) & 0x18) >> 3;
        func_02085a60(e, data_020d1ccc[tableIndex]);
        if (e->action < 5) {
            Boss_SetAnimation(e, 0);
        } else {
            Boss_SetAnimation(e, 2);
        }
        return;
    }
    case 0x36:
        Boss_StartDying(e);
        return;
    case 0:
        break;
    default:
        if (e->action == 1) {
            e->zVelocity = 0x16000;
            VB(e)->launchTimer = 0x1e0;
            Boss_StartAction3(e);
        }
        break;
    }
    GenericKnockback(e, data_020d1d40);
}

ARM void Boss_Destroy(Entity *e) {
    Boss_CheckWallDeath(e);
    func_02084788(e);
}

ARM void Boss_InitHitStun(Entity *e) {
    e->spriteSettings.b0 = 1;
    e->unk_2e = 2;
    e->hitbox = data_020d1cd4;
    e->action++;
    e->timer = 1;
    e->animationState = 0;
    VB(e)->flashTimer = 1;
    e->unk_1a = 0;
    InitAnimationForceUpdate(e, 0);
}

ARM void Boss_FloatAndTurn(Entity *e) {
    if (UpdateGravity(e, 0x1800) != 0) {
        return;
    }
    UpdateAnimationSingleFrame(e);
    if (--e->timer == 0) {
        e->timer = 0x1e;
        e->direction = (Random() & 0x18) + 4;
        Boss_SetAnimation(e, 0);
    }
    func_020847a0(e);
}

ARM void Boss_UpdateSubAction(Entity *e) {
    data_020d1d2c[e->subAction](e);
    Boss_UpdateLaunchWait(e);
}

ARM void Boss_InitMirrorPlayer(Entity *e) {
    e->subAction = 1;
    e->unk_5c = 0x3100;
    Entity *player = data_0212ceb0[e->type2].entity;
    VB(e)->mirroredAnim = player->animationState;
    VB(e)->poseLatched = 0;
    e->unk_2e = 0;
}

ARM void Boss_SyncMirrorAnim(Entity *e) {
    Entity *player = data_0212ceb0[e->type2].entity;
    if (((VB(e)->mirroredAnim ^ player->animationState) & 4) == 0) {
        return;
    }
    u8 ownAnim = e->animationState;
    VB(e)->mirroredAnim = player->animationState;
    e->animationState = ownAnim ^ 1;
    InitAnimationForceUpdate(e, e->animationState);
}

ARM void Boss_UpdatePose(Entity *e) {
    e->unk_2e = 2;
    if (VB(e)->poseLatched == 0) {
        VB(e)->poseLatched = 1;
        Entity *player = data_0212ceb0[e->type2].entity;
        e->unk_2c = *(const u16 *)(data_020d1cdc + (player->animationState & ~1));
    }
    Boss_CheckWallDeath(e);
}

ARM void Boss_ClearMotion(Entity *e) {
    Boss_StartAction3(e);
    e->unk_1a = 0;
}

ARM void Boss_UpdateGroundContact(Entity *e) {
    func_02086044(e, 0x2000);
    if (Boss_UpdateLaunchWait(e) == 0) {
        return;
    }
    func_02089524(e);
}

ARM void Boss_Dive(Entity *e) {
    e->spriteSettings.b14 = 1;
    e->spriteSettings.b30 = 1;
    if (UpdateGravity(e, 0x1800) != 0) {
        return;
    }
    e->action = 5;
    e->spriteSettings.b14 = 2;
    e->spriteSettings.b30 = 2;
    e->speed = 0x200;
    e->direction = (Random() & 0x18) + 4;
    Boss_SetAnimation(e, 2);
}

ARM void Boss_TickFlash(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (func_020847b0(e) != 0) {
        Boss_SetAnimation(e, 2);
    }
    if (--VB(e)->flashTimer != 0) {
        return;
    }
    VB(e)->flashTimer = 0x1e;
    EnqueueSFX(0x53);
}

ARM void Boss_Explode(Entity *e) {
    Entity *fx = CreateFx(0x20, 0xff, 0);
    if (fx != NULL) {
        CopyPosition(e, fx);
    }
    DeleteEntity(e);
}
