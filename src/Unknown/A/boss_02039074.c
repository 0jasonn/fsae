#include "Unknown/A/Boss_02039074.h"
#include "global.h"

ARM void func_02039074(Entity *e) {
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

ARM void func_020390d0(Entity *e) {
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
        func_02039278(e);
    }
    func_020847a0(e);
    UpdateAnimationSingleFrame(e);
}

ARM void func_02039160(Entity *e) {
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
        Entity *p = CreateProjectile(0);
        if (p != NULL) {
            p->direction = Random() & 0x1f;
            if (e->child != NULL) {
                p->direction = GetFacingDirection(e, e->child);
            } else {
                p->direction = Random() & 0x1f;
            }
            if (e->unk_09 != 5) {
                p->type = 1;
            }
            CopyPosition(e, p);
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

ARM void func_02039278(Entity *e) {
    u8 d = Random() & 0x1f;
    e->direction = d;
    u8 r = func_02045a8c(d);
    if (r == 0xff || r == e->animationState) {
        return;
    }
    e->animationState = r;
    InitAnimationForceUpdate(e, r);
}

ARM void func_020392b4(Entity *e) {
    switch (W(e)->unk_78) {
    case 0:
        if (UpdateGravity(e, 0x20000) != 0) {
            return;
        }
        e->unk_43 = 0;
        W(e)->unk_78++;
        W(e)->unk_7e = 0x1e0;
        e->unk_3c |= 0x80;
        e->unk_3f = 0x44;
        InitAnimationForceUpdate(e, 2);
        EnqueueSFX(0x16);
        break;
    case 1:
        UpdateAnimationSingleFrame(e);
        W(e)->unk_7e--;
        if (W(e)->unk_7e == 0) {
            W(e)->unk_78++;
            InitAnimationForceUpdate(e, 3);
            break;
        }
        if (W(e)->unk_7e < 0x3c) {
            e->x.HALF.HI += data_020d1998[W(e)->unk_7e & 3];
        }
        break;
    case 2:
        UpdateAnimationSingleFrame(e);
        if ((e->frame & 0x80) == 0) {
            break;
        }
        W(e)->unk_78 = 0;
        e->action = 1;
        e->timer = 1;
        e->subtimer = 0x10;
        e->speed = 0x80;
        e->animationState = 0;
        e->unk_3f = 6;
        e->health = V(e)->unk_7d;
        InitAnimationForceUpdate(e, 0);
        break;
    }
}

ARM void func_020393e8(Entity *e) {
    if (data_0212c540[1] > 1) {
        func_02084700(e);
    }
    int r = func_020849c8(e);
    if (r != 0) {
        func_02084ab8(e, r);
    } else {
        data_020d1a64[func_02084a30(e)](e);
    }
}

ARM void func_02039444(Entity *e) {
    func_02084700(e);
    data_020d1b94[func_02084a30(e)](e);
    func_0208ae30(e);
    e->spriteSettings.b30 = 1;
    e->spriteSettings.b14 = 1;
}

ARM void func_02039494(Entity *e) {
    data_020d1b84[e->action](e);
}

ARM void func_020394b0(Entity *e) {
    GenericKnockback(e, data_020d1b94);
}

ARM void func_020394c4(Entity *e) {
    e->spriteSettings.b0 = 1;
    e->unk_2e = 0;
    e->hitbox = data_020d1b8c;
    e->action++;
    e->direction = Random() & 0x1f;
    InitAnimationForceUpdate(e, 0);
}

ARM void func_02039518(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (e->frame & 0x80) {
        e->direction = Random() & 0x1f;
        InitAnimationForceUpdate(e, 0);
    } else {
        func_020847f8(e);
    }
    e->z.HALF.HI = data_020d1b7c[e->frame];
}

ARM void func_0203956c(Entity *e) {
    EnemyFunctionHandler(e, data_020d1c20);
}

ARM void func_02039580(Entity *e) {
    data_020d1c7c[e->action](e);
}

ARM void func_0203959c(Entity *e) {
    if (e->health != 0 && V(e)->unk_7c != e->health) {
        e->action = 9;
        return;
    }
    GenericKnockback(e, data_020d1c20);
}

ARM void func_020395cc(Entity *e) {
    e->spriteSettings.b0 = 1;
    e->unk_2e = 2;
    e->hitbox = data_020d1bcc;
    V(e)->unk_7c = e->health;
    InitAnimationForceUpdate(e, 0);
    e->action++;
    e->child = data_0212ceb0[0].unk_28;
    V(e)->unk_64 = func_02045eb4();
    e->direction = GetFacingDirection(e, V(e)->unk_64);
}

ARM void func_02039640(Entity *e) {
    e->action++;
    e->timer = (Random() & 0x30) + 0x20;
    InitAnimationForceUpdate(e, 0);
}

ARM void func_02039674(Entity *e) {
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

ARM void func_02039704(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if ((e->frame & 0x80) == 0) {
        return;
    }
    e->action++;
    e->zVelocity = 0x12000;
    e->z.HALF.HI = -8;
    if (func_0208de54(func_0208da4c()) == 0) {
        u8 p = *func_02093b5c();
        V(e)->unk_64 = data_0212ceb0[p].unk_28;
    }
    e->direction = func_02084fd0(e, V(e)->unk_64);
    InitAnimationForceUpdate(e, 2);
    EnqueueSFX(0x31);
}

ARM void func_02039790(Entity *e) {
    func_020847a0(e);
    UpdateAnimationSingleFrame(e);
    if (UpdateGravity(e, 0x1800) != 0) {
        return;
    }
    e->action++;
    InitAnimationForceUpdate(e, 3);
}

ARM void func_020397d4(Entity *e) {
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

ARM void func_02039818(Entity *e) {
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

ARM void func_0203987c(Entity *e) {
    if (--e->timer != 0) {
        return;
    }
    e->action++;
    e->spriteSettings.b0 = 1;
    InitAnimationForceUpdate(e, 5);
}

ARM void func_020398bc(Entity *e) {
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

ARM void func_0203990c(Entity *e) {
    s8 n = 0;
    Entity *a = CreateEnemy(3);
    if (a != NULL) {
        a->z.HALF.HI = 0;
        a->iframes = 0xf0;
        n++;
    }
    Entity *b = CreateEnemy(3);
    if (b != NULL) {
        b->z.HALF.HI = 0;
        b->iframes = 0xf0;
        n++;
    }
    func_02045c20(e, a, b);
    if (n == 2) {
        a->parent = b;
        a->type2 = 1;
        b->parent = a;
        b->type2 = 1;
    }
    if (e->unk_60 != NULL) {
        VARS(Vars_Target, e->unk_60)->unk_62 += (u16)n;
    }
    Entity *fx = CreateFx(0xf, 2, 0);
    if (fx != NULL) {
        CopyPosition(e, fx);
    }
    DeleteEntity(e);
}

ARM void func_020399d8(Entity *e) {
    EnemyFunctionHandler(e, data_020d1d40);
}

ARM void func_020399ec(Entity *e) {
    data_020d1d58[e->action](e);
    if (W(e)->unk_76 == 0) {
        return;
    }
    W(e)->unk_76--;
    if (W(e)->unk_76 == 0) {
        func_02039e58(e);
        return;
    }
    if (W(e)->unk_76 >= 0x3c) {
        return;
    }
    if ((W(e)->unk_76 & 1) == 0) {
        return;
    }
    if (e->spriteSettings.b16 == e->spriteSettings.b20) {
        e->spriteSettings.b16 = 0xe;
    } else {
        e->spriteSettings.b16 = e->spriteSettings.b20;
    }
}

ARM void func_02039a7c(Entity *e) {
    switch (e->contactFlags & 0x7f) {
    case 0x16:
        func_02039e58(e);
        return;
    case 1:
    case 2:
    case 3: {
        u8 k = e->animationState - 4;
        if (k < 2) {
            return;
        }
        u8 idx = ((e->unk_3e + 4) & 0x18) >> 3;
        func_02085a60(e, data_020d1ccc[idx]);
        if (e->action < 5) {
            func_02039e8c(e, 0);
        } else {
            func_02039e8c(e, 2);
        }
        return;
    }
    case 0x36:
        func_02039ed4(e);
        return;
    case 0:
        break;
    default:
        if (e->action == 1) {
            e->zVelocity = 0x16000;
            W(e)->unk_74 = 0x1e0;
            func_0203a168(e);
        }
        break;
    }
    GenericKnockback(e, data_020d1d40);
}

ARM void func_02039b70(Entity *e) {
    func_02039f24(e);
    func_02084788(e);
}

ARM void func_02039b88(Entity *e) {
    e->spriteSettings.b0 = 1;
    e->unk_2e = 2;
    e->hitbox = data_020d1cd4;
    e->action++;
    e->timer = 1;
    e->animationState = 0;
    W(e)->unk_73 = 1;
    e->unk_1a = 0;
    InitAnimationForceUpdate(e, 0);
}

ARM void func_02039bdc(Entity *e) {
    if (UpdateGravity(e, 0x1800) != 0) {
        return;
    }
    UpdateAnimationSingleFrame(e);
    if (--e->timer == 0) {
        e->timer = 0x1e;
        e->direction = (Random() & 0x18) + 4;
        func_02039e8c(e, 0);
    }
    func_020847a0(e);
}

ARM void func_02039c40(Entity *e) {
    data_020d1d2c[e->subAction](e);
    func_0203a07c(e);
}

ARM void func_02039c68(Entity *e) {
    e->subAction = 1;
    e->unk_5c = 0x3100;
    Entity *p = data_0212ceb0[e->type2].unk_28;
    W(e)->unk_71 = p->animationState;
    W(e)->unk_72 = 0;
    e->unk_2e = 0;
}

ARM void func_02039ca8(Entity *e) {
    Entity *p = data_0212ceb0[e->type2].unk_28;
    if (((W(e)->unk_71 ^ p->animationState) & 4) == 0) {
        return;
    }
    u8 anim = e->animationState;
    W(e)->unk_71 = p->animationState;
    e->animationState = anim ^ 1;
    InitAnimationForceUpdate(e, e->animationState);
}

ARM void func_02039cf4(Entity *e) {
    e->unk_2e = 2;
    if (W(e)->unk_72 == 0) {
        W(e)->unk_72 = 1;
        Entity *p = data_0212ceb0[e->type2].unk_28;
        e->unk_2c = *(const u16 *)(data_020d1cdc + (p->animationState & ~1));
    }
    func_02039f24(e);
}

ARM void func_02039d4c(Entity *e) {
    func_0203a168(e);
    e->unk_1a = 0;
}

ARM void func_02039d64(Entity *e) {
    func_02086044(e, 0x2000);
    if (func_0203a07c(e) == 0) {
        return;
    }
    func_02089524(e);
}

ARM void func_02039d90(Entity *e) {
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
    func_02039e8c(e, 2);
}

ARM void func_02039e08(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (func_020847b0(e) != 0) {
        func_02039e8c(e, 2);
    }
    if (--W(e)->unk_73 != 0) {
        return;
    }
    W(e)->unk_73 = 0x1e;
    EnqueueSFX(0x53);
}

ARM void func_02039e58(Entity *e) {
    Entity *fx = CreateFx(0x20, 0xff, 0);
    if (fx != NULL) {
        CopyPosition(e, fx);
    }
    DeleteEntity(e);
}
