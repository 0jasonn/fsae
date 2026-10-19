#include "engine/functions.h"
#include "enemy/em2d.h"
#include "global.h"

ARM void Em2d(Entity *e) {
    if (e->type == 0) {
        em2d_type0Actions[e->action](e);
        V(e)->cycleTimer--;
    } else {
        em2d_type1Actions[e->action](e);
    }
    if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) != 0) {
        return;
    }
    if (em2d_retargetState.lastPlayer != *Knife_Single_SinglePlay_GetInstance()) {
        em2d_retargetState.lastPlayer = *Knife_Single_SinglePlay_GetInstance();
        em2d_retargetState.retargetTimer = 0xb4;
    }
    if (em2d_retargetState.retargetTimer != 0) {
        em2d_retargetState.retargetTimer--;
    }
}

ARM void em2c_type0_init_034878(Entity *e) {
    if (kukiSet(e) == 0) {
        return;
    }
    switch (e->type2) {
        case 0:
            e->action = 1;
            e->timer = 0x78;
            e->subtimer = 0x96;
            e->speed = 0x100;
            e->health = em2d_healthType0[data_0212c7c8.stage - 1];
            V(e)->orbitRadius = 0x10;
            InitAnimationForceUpdate(e, 3);
            break;
        case 1: {
            e->action = 7;
            e->timer = 0x3c;
            e->health = em2d_healthType1[data_0212c7c8.stage - 1];
            V(e)->orbitRadius = 0x10;
            InitAnimationForceUpdate(e, 3);
            Entity *fx = GetSetWork(0xf, 2, 0x20);
            if (fx != NULL) {
                ObjPosCopy(e, fx);
            }
            break;
        }
        case 2: {
            e->action = 0xe;
            e->timer = 0x96;
            e->speed = 0x100;
            e->health = em2d_healthType2[data_0212c7c8.stage - 1];
            V(e)->orbitRadius = 0x10;
            e->direction = Random() & 0x1f;
            InitAnimationForceUpdate(e, (e->animationState = ((e->direction + 2) >> 2) & 7) + 0x14);
            Entity *fx = GetSetWork(0xf, 2, 0x20);
            if (fx != NULL) {
                ObjPosCopy(e, fx);
            }
            EnqueueSFX(0x9e);
            break;
        }
    }
    e->spriteSettings.b20 = e->parent->spriteSettings.b16;
    e->spriteSettings.b16 = e->spriteSettings.b20;
    e->spriteSettings.b0 = 1;
    e->hitbox = em2d_closeHitbox;
    V(e)->cycleTimer = Random();
    em2d_retargetState.retargetTimer = 0;
    em2d_retargetState.lastPlayer = 0;
}

ARM void type0_1stDemo(Entity *e) {
    if (data_0212c7c8.unk_5 & 0x80) {
        return;
    }
    if (e->timer != 0) {
        if (--e->timer != 0) {
            return;
        }
        InitAnimationForceUpdate(e, (e->animationState = ((e->direction + 0x10) >> 5) & 7) + 0x14);
        EnqueueSFX(0x9e);
    }
    ObjPosCopyOfs32(e->parent, e, (s16)((V(e)->orbitRadius * trigTable[e->direction]) >> 8) << 16,
                  (s16)(-4 - ((V(e)->orbitRadius * trigTable[e->direction + 0x40]) >> 8)) << 16);
    V(e)->orbitRadius++;
    if (V(e)->orbitRadius >= 0x40) {
        e->action = 2;
        e->timer = 0x3c;
    }
}

ARM void em2c_type0_1stDemoWait_034b44(Entity *e) {
    if (--e->timer != 0) {
        return;
    }
    e->action = 3;
    e->timer = 0x5a;
    e->speed = em2d_demoSpeeds[data_0212c7c8.stage - 1];
    VE(e->parent)->eventFlags |= (u8)flagBits[V(e)->eventBitIndex];
}

ARM void type0_1stWait(Entity *e) {
    cercleMoveC2(e);
    if (--e->timer != 0) {
        return;
    }
    e->action = 4;
    openInit(e);
    V(e)->petal->spriteSettings.b20 = e->spriteSettings.b20;
    V(e)->petal->spriteSettings.b16 = V(e)->petal->spriteSettings.b20;
}

ARM void type0_1stOpen(Entity *e) {
    cercleMove2(e);
    if (V(e)->petal != NULL) {
        UpdateAnimationSingleFrame(V(e)->petal);
    }
    UpdateAnimationSingleFrame(e);
    if (!(e->frame & 0x80)) {
        return;
    }
    e->action = 5;
    e->timer = 0x5a;
    openEndSet(e);
}

ARM void type0_1stCercle(Entity *e) {
    if (damagecheck(e) != 0 && e->health == 0) {
        flowerDie(e);
        return;
    }
    if (e->timer == 0) {
        if (e->iframes == 0) {
            e->action = 6;
            closeInit(e);
        }
    } else {
        e->timer--;
    }
    cercleMove2(e);
    if (V(e)->petal != NULL) {
        UpdateAnimationSingleFrame(V(e)->petal);
    }
}

ARM void type0_1stClose(Entity *e) {
    cercleMove2(e);
    if (V(e)->petal != NULL) {
        UpdateAnimationSingleFrame(V(e)->petal);
    }
    UpdateAnimationSingleFrame(e);
    if (!(e->frame & 0x80)) {
        return;
    }
    e->action = 3;
    e->timer = 0x3c;
    closeEndSet(e);
    InitAnimationForceUpdate(e, (e->animationState = ((e->direction + 2) >> 2) & 7) + 0x14);
}

ARM void type0_2ndDemo(Entity *e) {
    if (--e->timer != 0) {
        return;
    }
    e->action = 8;
    VE(e->parent)->eventFlags |= (u8)flagBits[V(e)->eventBitIndex];
    EnqueueSFX(0x9e);
}

ARM void type0_2ndGetdir(Entity *e) {
    if (e->timer != 0) {
        e->timer--;
        return;
    }
    e->action = 9;
    e->timer = (Random() & 0x3f) + 0xb4;
    if (data_0212c7c8.unk_0 != 2) {
        e->speed = 0x120;
    } else {
        e->speed = 0x100;
    }
    if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) == 0) {
        if (em2d_retargetState.retargetTimer == 0) {
            V(e)->aimTarget = data_0212ceb0[*Knife_Single_SinglePlay_GetInstance()].entity;
        }
        if (V(e)->aimTarget == NULL) {
            V(e)->aimTarget = EmGetAimPl();
        }
    } else {
        V(e)->aimTarget = EmGetAimPl();
    }
    if (V(e)->aimTarget == NULL) {
        return;
    }
    e->direction = func_02084fd0(e, V(e)->aimTarget);
    InitAnimationForceUpdate(e, (e->animationState = ((e->direction + 2) >> 2) & 7) + 0x14);
}

ARM void em2c_type0_2ndMove_034ea0(Entity *e) {
    if (V(e)->phaseFlags & 0x80) {
        e->action = 0xb;
        openInit(e);
        return;
    }
    if (e->contactFlags & 0x80) {
        u8 index = e->contactedEntity->type;
        if (index < 4) {
            V(e)->aimTarget = data_0212ceb0[index].entity;
        }
    }
    if (--e->timer != 0) {
        if ((e->timer & 3) == 0) {
            func_02086200(e, func_02084fd0(e, V(e)->aimTarget));
            int anim = ((e->direction + 2) >> 2) & 7;
            if (anim != e->animationState) {
                InitAnimationForceUpdate(e, (e->animationState = anim) + 0x14);
            }
        }
        MoveDir(e);
    } else {
        e->action = 0xa;
    }
}

ARM void type0_2ndAttack(Entity *e) {
    if (V(e)->phaseFlags & 0x80) {
        e->action = 0xb;
        openInit(e);
        ObjPosCopy(e->child, e);
        return;
    }
    UpdateAnimationSingleFrame(e);
    if (e->frame & 1) {
        e->frame = 0;
        seedSet(e);
        return;
    }
    if (e->frame & 0x80) {
        e->action = 8;
    }
}

ARM void type0_2ndOpen(Entity *e) {
    if (V(e)->petal != NULL) {
        UpdateAnimationSingleFrame(V(e)->petal);
    }
    UpdateAnimationSingleFrame(e);
    if (!(e->frame & 0x80)) {
        return;
    }
    e->action = 0xc;
    e->timer = 0xf0;
    openEndSet(e);
}

ARM void type0_2ndBlossom(Entity *e) {
    if (e->timer != 0) {
        e->timer--;
        if (damagecheck(e) == 0) {
            return;
        }
        if (e->health != 0) {
            return;
        }
        flowerDie(e);
        return;
    }
    if (e->iframes != 0) {
        return;
    }
    e->action = 0xd;
    closeInit(e);
}

ARM void type0_2ndClose(Entity *e) {
    if (V(e)->petal != NULL) {
        UpdateAnimationSingleFrame(V(e)->petal);
    }
    UpdateAnimationSingleFrame(e);
    if (!(e->frame & 0x80)) {
        return;
    }
    e->action = 8;
    e->timer = 0x1e;
    V(e)->orbitRadius = 0x10;
    closeEndSet(e);
}

ARM void type0_3rdDemo(Entity *e) {
    MoveDir(e);
    if (--e->timer != 0) {
        return;
    }
    e->action = 0xf;
    e->speed = em2d_thirdDemoSpeeds[data_0212c7c8.stage - 1];
    V(e)->phaseFlags = 1;
    VE(e->parent)->eventFlags |= (u8)flagBits[V(e)->eventBitIndex];
}

ARM void type0_3rdCercle(Entity *e) {
    if ((V(e)->phaseFlags & 0xc0) == 0xc0) {
        e->action = 0x10;
        openInit(e);
        differentColSet(e);
        ObjPosCopy(e->child, e);
        return;
    }
    V(e)->phaseFlags &= 0x3f;
    cercleMoveC(e);
}

ARM void type0_3rdOpen(Entity *e) {
    if (V(e)->petal != NULL) {
        UpdateAnimationSingleFrame(V(e)->petal);
    }
    UpdateAnimationSingleFrame(e);
    if (!(e->frame & 0x80)) {
        return;
    }
    e->action = 0x11;
    e->timer = 0xf0;
    openEndSet(e);
}

ARM void type0_3rdBlossom(Entity *e) {
    if (e->timer != 0) {
        e->timer--;
        if (damagecheck(e) == 0) {
            return;
        }
        if (e->health != 0) {
            return;
        }
        e->health = 0xff;
        e->action = 0x16;
        e->timer = 0xb4;
        e->statusFlags &= 0x7f;
        e->unk_5e.b0 = 3;
        if (V(e)->petal != NULL) {
            V(e)->petal->statusFlags &= 0x7f;
            V(e)->petal->unk_5e.b0 = 3;
        }
        e->direction = Random() & 0xf;
        e->speed = 0x400;
        V(e)->orbitRadius = 0xf;
        V(e->parent)->phaseFlags = 0xffff;
        return;
    }
    if (e->iframes != 0) {
        return;
    }
    e->action = 0x12;
    V(e)->phaseFlags ^= 2;
    closeInit(e);
}

ARM void type0_3rdClose(Entity *e) {
    if (V(e)->petal != NULL) {
        UpdateAnimationSingleFrame(V(e)->petal);
    }
    UpdateAnimationSingleFrame(e);
    if (!(e->frame & 0x80)) {
        return;
    }
    V(e)->orbitRadius = 0x10;
    closeEndSet(e);
    if (V(e)->phaseFlags & 2) {
        e->action = 0x13;
        e->timer = 0x1e;
        return;
    }
    e->action = 0xe;
    e->timer = 0x96;
    e->speed = 0x100;
    e->direction = GetFacingDirection(e->parent, e);
    InitAnimationForceUpdate(e, (e->animationState = ((e->direction + 2) >> 2) & 7) + 0x14);
}

ARM void type0_3rdAimInit(Entity *e) {
    if (e->timer != 0) {
        e->timer--;
        return;
    }
    e->action = 0x14;
    e->timer = 0x78;
    e->speed = 0x120;
    if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) == 0) {
        if (em2d_retargetState.retargetTimer == 0) {
            V(e)->aimTarget = data_0212ceb0[*Knife_Single_SinglePlay_GetInstance()].entity;
        }
        if (V(e)->aimTarget == NULL) {
            V(e)->aimTarget = EmGetAimPl();
        }
    } else {
        V(e)->aimTarget = EmGetAimPl();
    }
    e->direction = func_02084fd0(e, V(e)->aimTarget);
    InitAnimationForceUpdate(e, (e->animationState = ((e->direction + 2) >> 2) & 7) + 0x14);
}

ARM void type0_3rdAimMove(Entity *e) {
    if ((V(e)->phaseFlags & 0xc0) == 0xc0) {
        e->action = 0x10;
        openInit(e);
        differentColSet(e);
        ObjPosCopy(e->child, e);
        return;
    }
    V(e)->phaseFlags &= 0x3f;
    if ((e->contactFlags & 0x80) && e->contactedEntity->type < 4) {
        if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) == 0) {
            if (em2d_retargetState.retargetTimer == 0) {
                V(e)->aimTarget = data_0212ceb0[*Knife_Single_SinglePlay_GetInstance()].entity;
            }
            if (V(e)->aimTarget == NULL) {
                V(e)->aimTarget = data_0212ceb0[e->contactedEntity->type].entity;
            }
        } else {
            V(e)->aimTarget = data_0212ceb0[e->contactedEntity->type].entity;
        }
    }
    if (--e->timer != 0) {
        if ((e->timer & 3) == 0) {
            func_02086200(e, func_02084fd0(e, V(e)->aimTarget));
            int anim = ((e->direction + 2) >> 2) & 7;
            if (anim != e->animationState) {
                InitAnimationForceUpdate(e, (e->animationState = anim) + 0x14);
            }
        }
        MoveDir(e);
    } else {
        e->action = 0x15;
    }
}

ARM void type0_3rdAttack(Entity *e) {
    if ((V(e)->phaseFlags & 0xc0) == 0xc0) {
        e->action = 0x10;
        openInit(e);
        differentColSet(e);
        ObjPosCopy(e->child, e);
        return;
    }
    V(e)->phaseFlags &= 0x3f;
    UpdateAnimationSingleFrame(e);
    if (e->frame & 1) {
        e->frame = 0;
        seedSet(e);
        return;
    }
    if (e->frame & 0x80) {
        e->action = 0x13;
    }
}

ARM void type0_DieDemo0(Entity *e) {
    if (e->iframes != 0) {
        return;
    }
    if (--e->timer == 0) {
        e->action = 0x17;
        return;
    }
    if ((e->timer & 0xf) == 0) {
        e->direction = Random() & 0x1f;
        SoundReq(0x2e);
    }
    MoveDir(e);
}

ARM void type0_DieDemo1(Entity *e) {
    e->x.HALF.HI += em2d_dieSway[e->timer & 3];
    if (++e->timer >= 0x3c) {
        e->timer = 0x1e;
        e->action = 0x18;
    }
}

ARM void type0_DieDemo2(Entity *e) {
    if (--e->timer != 0) {
        return;
    }
    flowerDie(e);
}

ARM void em2c_type1_init_0356bc(Entity *e) {
    e->action = 1;
    e->health = 0xff;
    e->statusFlags &= 0x7f;
    e->poseId = 0x3f;
    e->hitbox = em2d_type1Hitbox;
}

ARM void em2c_type1_wait_0356f4(Entity *e) {
    Entity *parent = e->parent;
    if (parent->type2 != 0 || VCT(parent->parent)->flowerCount != 1) {
        return;
    }
    if (!(e->statusFlags & 0x80)) {
        return;
    }
    e->action = 2;
    e->timer = (Random() + 0x1e) & 0xf;
}

ARM void type1_attackWait(Entity *e) {
    if (--e->timer == 0) {
        e->action = 3;
        InitAnimationForceUpdate(e, 9);
    }
    if (!(e->statusFlags & 0x80)) {
        e->action = 1;
    }
}

ARM void type1_attack(Entity *e) {
    e->z.HALF.HI = em2d_attackZ[(e->frame >> 4) & 3];
    e->parent->z.HALF.HI = e->z.HALF.HI;
    if (e->frame & 1) {
        Entity *proj = GetTamaWork(0xd);
        if (proj != NULL) {
            proj->direction = GetFacingDirection(e, data_0212ceb0[Random() % data_0212c7c8.unk_0].entity);
            ObjPosCopy(e, proj);
            e->frame = 0;
            EnqueueSFX(0xa5);
        }
    } else if (e->frame == 0x80) {
        e->action = 2;
        e->timer = (Random() + 0x1e) & 0xf;
        InitAnimationForceUpdate(e, 8);
    }
    if (!(e->statusFlags & 0x80)) {
        e->action = 1;
    }
}

ARM void damageSet(Entity *e, Entity *src) {
    V(e)->phaseFlags |= 1;
    u8 damage = src->contactedEntity->attackDamage;
    if (e->health < damage) {
        e->health = 0;
    } else {
        e->health -= damage;
    }
    e->iframes = src->contactedEntity->attackKnockback < 0 ? -0x10 - src->contactedEntity->attackKnockback : src->contactedEntity->attackKnockback + 0x10;
    if (V(e)->petal != NULL) {
        V(e)->petal->iframes = e->iframes;
    }
    EnqueueSFX(0x2d);
}

ARM BOOL damagecheck(Entity *e) {
    Entity *other = V(e)->petal;
    if (other != NULL && other->spriteSettings.b20 == e->spriteSettings.b20) {
        if (e->contactFlags & 0x80) {
            if ((u16)(e->contactFlags - 0x84) <= 0x9f) {
                if (e->spriteSettings.b20 - 7 == e->contactedEntity->type) {
                    damageSet(e, e);
                    return TRUE;
                }
            } else {
                e->iframes = 0xf8;
                other->iframes = 0xf8;
            }
        } else if (other->contactFlags & 0x80) {
            if ((u16)(other->contactFlags - 0x84) <= 0x9f) {
                if (other->spriteSettings.b20 - 7 == other->contactedEntity->type) {
                    damageSet(e, other);
                    return TRUE;
                }
            } else {
                e->iframes = 0xf8;
                other->iframes = 0xf8;
            }
        }
    } else {
        u32 flags = 0;
        if ((e->contactFlags & 0x80) && (u16)(e->contactFlags - 0x84) <= 0x9f) {
            flags = 0x10;
            if (e->spriteSettings.b20 - 7 == e->contactedEntity->type) {
                flags |= 1;
            }
        }
        if (other != NULL && (other->contactFlags & 0x80) && (u16)(other->contactFlags - 0x84) <= 0x9f) {
            flags |= 0x20;
            if (other->spriteSettings.b20 - 7 == other->contactedEntity->type) {
                flags |= 2;
            }
        }
        if (flags != 0) {
            if ((flags & 3) == 3) {
                Entity *src = e;
                if (other != NULL && e->contactedEntity->attackDamage < other->contactedEntity->attackDamage) {
                    src = other;
                }
                damageSet(e, src);
                return TRUE;
            }
            if ((flags & 3) == 0) {
                e->iframes = 0xf8;
                if (V(e)->petal != NULL) {
                    V(e)->petal->iframes = 0xf8;
                }
            }
        }
    }
    return FALSE;
}
