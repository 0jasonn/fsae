#include "enemy/em05.h"
#include "global.h"

// Function names (dsd -> name), also in scratch/agentA/renames.txt:
// em05_press em05_press, em05_move2 em05_move2, em05_nage em05_nage,
// em05DirChange em05DirChange, em0d_die em0d_die, Em0d Em0d,
// Em06 Em06, em06_normal em06_normal, Boss_Knockback Boss_Knockback,
// em06_init em06_init, em06_move em06_move, Boss_HandleEnemyState Boss_HandleEnemyState,
// em07_normal em07_normal, em07_damage em07_damage, em07_init em07_init,
// em07_moveInit em07_moveInit, em07_move em07_move, em07_tame em07_tame,
// em07_jump em07_jump, em07_land em07_land, em07_vanish em07_vanish,
// em07_hide em07_hide, em07_appear em07_appear, em07_div em07_div,
// Boss_UpdateHitStates Boss_UpdateHitStates, em08_normal em08_normal, em08_damage em08_damage,
// em08_buttobi em08_buttobi, em08_init em08_init, em08_move em08_move,
// em08_lift em08_lift, em08_lift_init em08_lift_init, em08_lift_move em08_lift_move,
// em08_lift_throw em08_lift_throw, em08_lift_end em08_lift_end, em08_piyori em08_piyori,
// em08_jump em08_jump, em08_dush em08_dush, explodeSet explodeSet,
// em08_seqSet em08_seqSet (nonmatching, see scratch/agentA/nonmatching)

ARM void em05_press(Entity *e) {
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

ARM void em05_move2(Entity *e) {
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
        em05DirChange(e);
    }
    func_020847a0(e);
    UpdateAnimationSingleFrame(e);
}

ARM void em05_nage(Entity *e) {
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
        Entity *projectile = GetTamaWork(0);
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
            ObjPosCopy(e, projectile);
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

ARM void em05DirChange(Entity *e) {
    u8 direction = Random() & 0x1f;
    e->direction = direction;
    u8 newAnim = EmCharDir2(direction);
    if (newAnim == 0xff || newAnim == e->animationState) {
        return;
    }
    e->animationState = newAnim;
    InitAnimationForceUpdate(e, newAnim);
}

ARM void em0d_die(Entity *e) {
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

ARM void Em0d(Entity *e) {
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

ARM void Em06(Entity *e) {
    func_02084700(e);
    data_020d1b94[func_02084a30(e)](e);
    func_0208ae30(e);
    e->spriteSettings.b30 = 1;
    e->spriteSettings.b14 = 1;
}

ARM void em06_normal(Entity *e) {
    data_020d1b84[e->action](e);
}

ARM void Boss_Knockback(Entity *e) {
    GenericKnockback(e, data_020d1b94);
}

ARM void em06_init(Entity *e) {
    e->spriteSettings.b0 = 1;
    e->unk_2e = 0;
    e->hitbox = data_020d1b8c;
    e->action++;
    e->direction = Random() & 0x1f;
    InitAnimationForceUpdate(e, 0);
}

ARM void em06_move(Entity *e) {
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

ARM void em07_normal(Entity *e) {
    data_020d1c7c[e->action](e);
}

ARM void em07_damage(Entity *e) {
    if (e->health != 0 && VB(e)->lastHealth != e->health) {
        e->action = 9;
        return;
    }
    GenericKnockback(e, data_020d1c20);
}

ARM void em07_init(Entity *e) {
    e->spriteSettings.b0 = 1;
    e->unk_2e = 2;
    e->hitbox = data_020d1bcc;
    VB(e)->lastHealth = e->health;
    InitAnimationForceUpdate(e, 0);
    e->action++;
    e->child = data_0212ceb0[0].entity;
    VB(e)->target = EmGetAimPl();
    e->direction = GetFacingDirection(e, VB(e)->target);
}

ARM void em07_moveInit(Entity *e) {
    e->action++;
    e->timer = (Random() & 0x30) + 0x20;
    InitAnimationForceUpdate(e, 0);
}

ARM void em07_move(Entity *e) {
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

ARM void em07_tame(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if ((e->frame & 0x80) == 0) {
        return;
    }
    e->action++;
    e->zVelocity = 0x12000;
    e->z.HALF.HI = -8;
    if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) == 0) {
        u8 playerIndex = *Knife_Single_SinglePlay_GetInstance();
        VB(e)->target = data_0212ceb0[playerIndex].entity;
    }
    e->direction = func_02084fd0(e, VB(e)->target);
    InitAnimationForceUpdate(e, 2);
    EnqueueSFX(0x31);
}

ARM void em07_jump(Entity *e) {
    func_020847a0(e);
    UpdateAnimationSingleFrame(e);
    if (UpdateGravity(e, 0x1800) != 0) {
        return;
    }
    e->action++;
    InitAnimationForceUpdate(e, 3);
}

ARM void em07_land(Entity *e) {
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

ARM void em07_vanish(Entity *e) {
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

ARM void em07_hide(Entity *e) {
    if (--e->timer != 0) {
        return;
    }
    e->action++;
    e->spriteSettings.b0 = 1;
    InitAnimationForceUpdate(e, 5);
}

ARM void em07_appear(Entity *e) {
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

ARM void em07_div(Entity *e) {
    s8 count = 0;
    Entity *pieceA = GetEnemyWork(3);
    if (pieceA != NULL) {
        pieceA->z.HALF.HI = 0;
        pieceA->iframes = 0xf0;
        count++;
    }
    Entity *pieceB = GetEnemyWork(3);
    if (pieceB != NULL) {
        pieceB->z.HALF.HI = 0;
        pieceB->iframes = 0xf0;
        count++;
    }
    EmDivPosSet(e, pieceA, pieceB);
    if (count == 2) {
        pieceA->parent = pieceB;
        pieceA->type2 = 1;
        pieceB->parent = pieceA;
        pieceB->type2 = 1;
    }
    if (e->unk_60 != NULL) {
        VARS(Vars_Target, e->unk_60)->pieceCount += (u16)count;
    }
    Entity *fx = GetSetWork(0xf, 2, 0);
    if (fx != NULL) {
        ObjPosCopy(e, fx);
    }
    PutObjWork(e);
}

ARM void Boss_UpdateHitStates(Entity *e) {
    EnemyFunctionHandler(e, data_020d1d40);
}

ARM void em08_normal(Entity *e) {
    data_020d1d58[e->action](e);
    if (VB(e)->dyingTimer == 0) {
        return;
    }
    VB(e)->dyingTimer--;
    if (VB(e)->dyingTimer == 0) {
        explodeSet(e);
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

ARM void em08_damage(Entity *e) {
    switch (e->contactFlags & 0x7f) {
    case 0x16:
        explodeSet(e);
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
            em08_seqSet(e, 0);
        } else {
            em08_seqSet(e, 2);
        }
        return;
    }
    case 0x36:
        tenka(e);
        return;
    case 0:
        break;
    default:
        if (e->action == 1) {
            e->zVelocity = 0x16000;
            VB(e)->launchTimer = 0x1e0;
            piyoriSet(e);
        }
        break;
    }
    GenericKnockback(e, data_020d1d40);
}

ARM void em08_buttobi(Entity *e) {
    searchCandle(e);
    func_02084788(e);
}

ARM void em08_init(Entity *e) {
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

ARM void em08_move(Entity *e) {
    if (UpdateGravity(e, 0x1800) != 0) {
        return;
    }
    UpdateAnimationSingleFrame(e);
    if (--e->timer == 0) {
        e->timer = 0x1e;
        e->direction = (Random() & 0x18) + 4;
        em08_seqSet(e, 0);
    }
    func_020847a0(e);
}

ARM void em08_lift(Entity *e) {
    data_020d1d2c[e->subAction](e);
    purupuru(e);
}

ARM void em08_lift_init(Entity *e) {
    e->subAction = 1;
    e->unk_5c = 0x3100;
    Entity *player = data_0212ceb0[e->type2].entity;
    VB(e)->mirroredAnim = player->animationState;
    VB(e)->poseLatched = 0;
    e->unk_2e = 0;
}

ARM void em08_lift_move(Entity *e) {
    Entity *player = data_0212ceb0[e->type2].entity;
    if (((VB(e)->mirroredAnim ^ player->animationState) & 4) == 0) {
        return;
    }
    u8 ownAnim = e->animationState;
    VB(e)->mirroredAnim = player->animationState;
    e->animationState = ownAnim ^ 1;
    InitAnimationForceUpdate(e, e->animationState);
}

ARM void em08_lift_throw(Entity *e) {
    e->unk_2e = 2;
    if (VB(e)->poseLatched == 0) {
        VB(e)->poseLatched = 1;
        Entity *player = data_0212ceb0[e->type2].entity;
        e->unk_2c = *(const u16 *)(data_020d1cdc + (player->animationState & ~1));
    }
    searchCandle(e);
}

ARM void em08_lift_end(Entity *e) {
    piyoriSet(e);
    e->unk_1a = 0;
}

ARM void em08_piyori(Entity *e) {
    func_02086044(e, 0x2000);
    if (purupuru(e) == 0) {
        return;
    }
    func_02089524(e);
}

ARM void em08_jump(Entity *e) {
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
    em08_seqSet(e, 2);
}

ARM void em08_dush(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (func_020847b0(e) != 0) {
        em08_seqSet(e, 2);
    }
    if (--VB(e)->flashTimer != 0) {
        return;
    }
    VB(e)->flashTimer = 0x1e;
    EnqueueSFX(0x53);
}

ARM void explodeSet(Entity *e) {
    Entity *fx = GetSetWork(0x20, 0xff, 0);
    if (fx != NULL) {
        ObjPosCopy(e, fx);
    }
    PutObjWork(e);
}
