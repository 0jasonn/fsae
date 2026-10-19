#include "engine/functions.h"
#include "enemy/em2d.h"
#include "global.h"

ARM void Em2d(Entity *e) {
    if (e->type == 0) {
        data_020d11e0[e->action](e);
        V(e)->unk_7f--;
    } else {
        data_020d11c0[e->action](e);
    }
    if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) != 0) {
        return;
    }
    if (data_021348c0.unk_4 != *Knife_Single_SinglePlay_GetInstance()) {
        data_021348c0.unk_4 = *Knife_Single_SinglePlay_GetInstance();
        data_021348c0.unk_0 = 0xb4;
    }
    if (data_021348c0.unk_0 != 0) {
        data_021348c0.unk_0--;
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
            e->health = data_020f266e[data_0212c7c8.unk_6 - 1];
            V(e)->unk_7c = 0x10;
            InitAnimationForceUpdate(e, 3);
            break;
        case 1: {
            e->action = 7;
            e->timer = 0x3c;
            e->health = data_020f266b[data_0212c7c8.unk_6 - 1];
            V(e)->unk_7c = 0x10;
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
            e->health = data_020f2668[data_0212c7c8.unk_6 - 1];
            V(e)->unk_7c = 0x10;
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
    e->hitbox = data_020d119c;
    V(e)->unk_7f = Random();
    data_021348c0.unk_0 = 0;
    data_021348c0.unk_4 = 0;
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
    ObjPosCopyOfs32(e->parent, e, (s16)((V(e)->unk_7c * data_020d7e58[e->direction]) >> 8) << 16,
                  (s16)(-4 - ((V(e)->unk_7c * data_020d7e58[e->direction + 0x40]) >> 8)) << 16);
    V(e)->unk_7c++;
    if (V(e)->unk_7c >= 0x40) {
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
    e->speed = data_020f267a[data_0212c7c8.unk_6 - 1];
    VE(e->parent)->unk_7d |= (u8)data_020cf9b8[V(e)->unk_7e];
}

ARM void type0_1stWait(Entity *e) {
    cercleMoveC2(e);
    if (--e->timer != 0) {
        return;
    }
    e->action = 4;
    openInit(e);
    V(e)->unk_70->spriteSettings.b20 = e->spriteSettings.b20;
    V(e)->unk_70->spriteSettings.b16 = V(e)->unk_70->spriteSettings.b20;
}

ARM void type0_1stOpen(Entity *e) {
    cercleMove2(e);
    if (V(e)->unk_70 != NULL) {
        UpdateAnimationSingleFrame(V(e)->unk_70);
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
    if (V(e)->unk_70 != NULL) {
        UpdateAnimationSingleFrame(V(e)->unk_70);
    }
}

ARM void type0_1stClose(Entity *e) {
    cercleMove2(e);
    if (V(e)->unk_70 != NULL) {
        UpdateAnimationSingleFrame(V(e)->unk_70);
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
    VE(e->parent)->unk_7d |= (u8)data_020cf9b8[V(e)->unk_7e];
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
        if (data_021348c0.unk_0 == 0) {
            V(e)->unk_64 = data_0212ceb0[*Knife_Single_SinglePlay_GetInstance()].entity;
        }
        if (V(e)->unk_64 == NULL) {
            V(e)->unk_64 = EmGetAimPl();
        }
    } else {
        V(e)->unk_64 = EmGetAimPl();
    }
    if (V(e)->unk_64 == NULL) {
        return;
    }
    e->direction = func_02084fd0(e, V(e)->unk_64);
    InitAnimationForceUpdate(e, (e->animationState = ((e->direction + 2) >> 2) & 7) + 0x14);
}

ARM void em2c_type0_2ndMove_034ea0(Entity *e) {
    if (V(e)->unk_6e & 0x80) {
        e->action = 0xb;
        openInit(e);
        return;
    }
    if (e->contactFlags & 0x80) {
        u8 index = e->contactedEntity->type;
        if (index < 4) {
            V(e)->unk_64 = data_0212ceb0[index].entity;
        }
    }
    if (--e->timer != 0) {
        if ((e->timer & 3) == 0) {
            func_02086200(e, func_02084fd0(e, V(e)->unk_64));
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
    if (V(e)->unk_6e & 0x80) {
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
    if (V(e)->unk_70 != NULL) {
        UpdateAnimationSingleFrame(V(e)->unk_70);
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
    if (V(e)->unk_70 != NULL) {
        UpdateAnimationSingleFrame(V(e)->unk_70);
    }
    UpdateAnimationSingleFrame(e);
    if (!(e->frame & 0x80)) {
        return;
    }
    e->action = 8;
    e->timer = 0x1e;
    V(e)->unk_7c = 0x10;
    closeEndSet(e);
}

ARM void type0_3rdDemo(Entity *e) {
    MoveDir(e);
    if (--e->timer != 0) {
        return;
    }
    e->action = 0xf;
    e->speed = data_020f2680[data_0212c7c8.unk_6 - 1];
    V(e)->unk_6e = 1;
    VE(e->parent)->unk_7d |= (u8)data_020cf9b8[V(e)->unk_7e];
}

ARM void type0_3rdCercle(Entity *e) {
    if ((V(e)->unk_6e & 0xc0) == 0xc0) {
        e->action = 0x10;
        openInit(e);
        differentColSet(e);
        ObjPosCopy(e->child, e);
        return;
    }
    V(e)->unk_6e &= 0x3f;
    cercleMoveC(e);
}

ARM void type0_3rdOpen(Entity *e) {
    if (V(e)->unk_70 != NULL) {
        UpdateAnimationSingleFrame(V(e)->unk_70);
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
        e->unk_3c &= 0x7f;
        e->unk_5e.b0 = 3;
        if (V(e)->unk_70 != NULL) {
            V(e)->unk_70->unk_3c &= 0x7f;
            V(e)->unk_70->unk_5e.b0 = 3;
        }
        e->direction = Random() & 0xf;
        e->speed = 0x400;
        V(e)->unk_7c = 0xf;
        V(e->parent)->unk_6e = 0xffff;
        return;
    }
    if (e->iframes != 0) {
        return;
    }
    e->action = 0x12;
    V(e)->unk_6e ^= 2;
    closeInit(e);
}

ARM void type0_3rdClose(Entity *e) {
    if (V(e)->unk_70 != NULL) {
        UpdateAnimationSingleFrame(V(e)->unk_70);
    }
    UpdateAnimationSingleFrame(e);
    if (!(e->frame & 0x80)) {
        return;
    }
    V(e)->unk_7c = 0x10;
    closeEndSet(e);
    if (V(e)->unk_6e & 2) {
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
        if (data_021348c0.unk_0 == 0) {
            V(e)->unk_64 = data_0212ceb0[*Knife_Single_SinglePlay_GetInstance()].entity;
        }
        if (V(e)->unk_64 == NULL) {
            V(e)->unk_64 = EmGetAimPl();
        }
    } else {
        V(e)->unk_64 = EmGetAimPl();
    }
    e->direction = func_02084fd0(e, V(e)->unk_64);
    InitAnimationForceUpdate(e, (e->animationState = ((e->direction + 2) >> 2) & 7) + 0x14);
}

ARM void type0_3rdAimMove(Entity *e) {
    if ((V(e)->unk_6e & 0xc0) == 0xc0) {
        e->action = 0x10;
        openInit(e);
        differentColSet(e);
        ObjPosCopy(e->child, e);
        return;
    }
    V(e)->unk_6e &= 0x3f;
    if ((e->contactFlags & 0x80) && e->contactedEntity->type < 4) {
        if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) == 0) {
            if (data_021348c0.unk_0 == 0) {
                V(e)->unk_64 = data_0212ceb0[*Knife_Single_SinglePlay_GetInstance()].entity;
            }
            if (V(e)->unk_64 == NULL) {
                V(e)->unk_64 = data_0212ceb0[e->contactedEntity->type].entity;
            }
        } else {
            V(e)->unk_64 = data_0212ceb0[e->contactedEntity->type].entity;
        }
    }
    if (--e->timer != 0) {
        if ((e->timer & 3) == 0) {
            func_02086200(e, func_02084fd0(e, V(e)->unk_64));
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
    if ((V(e)->unk_6e & 0xc0) == 0xc0) {
        e->action = 0x10;
        openInit(e);
        differentColSet(e);
        ObjPosCopy(e->child, e);
        return;
    }
    V(e)->unk_6e &= 0x3f;
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
    e->x.HALF.HI += data_020f2675[e->timer & 3];
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
    e->unk_3c &= 0x7f;
    e->unk_3f = 0x3f;
    e->hitbox = data_020d11ac;
}

ARM void em2c_type1_wait_0356f4(Entity *e) {
    Entity *parent = e->parent;
    if (parent->type2 != 0 || VCT(parent->parent)->unk_7c != 1) {
        return;
    }
    if (!(e->unk_3c & 0x80)) {
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
    if (!(e->unk_3c & 0x80)) {
        e->action = 1;
    }
}

ARM void type1_attack(Entity *e) {
    e->z.HALF.HI = data_020f2671[(e->frame >> 4) & 3];
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
    if (!(e->unk_3c & 0x80)) {
        e->action = 1;
    }
}

ARM void damageSet(Entity *e, Entity *src) {
    V(e)->unk_6e |= 1;
    u8 damage = src->contactedEntity->unk_44;
    if (e->health < damage) {
        e->health = 0;
    } else {
        e->health -= damage;
    }
    e->iframes = src->contactedEntity->unk_46 < 0 ? -0x10 - src->contactedEntity->unk_46 : src->contactedEntity->unk_46 + 0x10;
    if (V(e)->unk_70 != NULL) {
        V(e)->unk_70->iframes = e->iframes;
    }
    EnqueueSFX(0x2d);
}

ARM BOOL damagecheck(Entity *e) {
    Entity *other = V(e)->unk_70;
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
                if (other != NULL && e->contactedEntity->unk_44 < other->contactedEntity->unk_44) {
                    src = other;
                }
                damageSet(e, src);
                return TRUE;
            }
            if ((flags & 3) == 0) {
                e->iframes = 0xf8;
                if (V(e)->unk_70 != NULL) {
                    V(e)->unk_70->iframes = 0xf8;
                }
            }
        }
    }
    return FALSE;
}
