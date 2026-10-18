#include "enemy/enemy_020347dc.h"
#include "global.h"

ARM void func_020347dc(Entity *e) {
    if (e->type == 0) {
        data_020d11e0[e->action](e);
        V(e)->unk_7f--;
    } else {
        data_020d11c0[e->action](e);
    }
    if (func_0208de54(func_0208da4c()) != 0) {
        return;
    }
    if (data_021348c0.unk_4 != *func_02093b5c()) {
        data_021348c0.unk_4 = *func_02093b5c();
        data_021348c0.unk_0 = 0xb4;
    }
    if (data_021348c0.unk_0 != 0) {
        data_021348c0.unk_0--;
    }
}

ARM void func_02034878(Entity *e) {
    if (func_02035d50(e) == 0) {
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
            Entity *fx = CreateFx(0xf, 2, 0x20);
            if (fx != NULL) {
                CopyPosition(e, fx);
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
            Entity *fx = CreateFx(0xf, 2, 0x20);
            if (fx != NULL) {
                CopyPosition(e, fx);
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

ARM void func_02034a64(Entity *e) {
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
    PositionRelative(e->parent, e, (s16)((V(e)->unk_7c * data_020d7e58[e->direction]) >> 8) << 16,
                  (s16)(-4 - ((V(e)->unk_7c * data_020d7e58[e->direction + 0x40]) >> 8)) << 16);
    V(e)->unk_7c++;
    if (V(e)->unk_7c >= 0x40) {
        e->action = 2;
        e->timer = 0x3c;
    }
}

ARM void func_02034b44(Entity *e) {
    if (--e->timer != 0) {
        return;
    }
    e->action = 3;
    e->timer = 0x5a;
    e->speed = data_020f267a[data_0212c7c8.unk_6 - 1];
    VE(e->parent)->unk_7d |= (u8)data_020cf9b8[V(e)->unk_7e];
}

ARM void func_02034bb4(Entity *e) {
    func_020360c0(e);
    if (--e->timer != 0) {
        return;
    }
    e->action = 4;
    func_02035a8c(e);
    V(e)->unk_70->spriteSettings.b20 = e->spriteSettings.b20;
    V(e)->unk_70->spriteSettings.b16 = V(e)->unk_70->spriteSettings.b20;
}

ARM void func_02034c2c(Entity *e) {
    func_02036064(e);
    if (V(e)->unk_70 != NULL) {
        UpdateAnimationSingleFrame(V(e)->unk_70);
    }
    UpdateAnimationSingleFrame(e);
    if (!(e->frame & 0x80)) {
        return;
    }
    e->action = 5;
    e->timer = 0x5a;
    func_02035c3c(e);
}

ARM void func_02034c78(Entity *e) {
    if (func_020358c4(e) != 0 && e->health == 0) {
        func_02035f18(e);
        return;
    }
    if (e->timer == 0) {
        if (e->iframes == 0) {
            e->action = 6;
            func_02035c98(e);
        }
    } else {
        e->timer--;
    }
    func_02036064(e);
    if (V(e)->unk_70 != NULL) {
        UpdateAnimationSingleFrame(V(e)->unk_70);
    }
}

ARM void func_02034cf4(Entity *e) {
    func_02036064(e);
    if (V(e)->unk_70 != NULL) {
        UpdateAnimationSingleFrame(V(e)->unk_70);
    }
    UpdateAnimationSingleFrame(e);
    if (!(e->frame & 0x80)) {
        return;
    }
    e->action = 3;
    e->timer = 0x3c;
    func_02035ce8(e);
    InitAnimationForceUpdate(e, (e->animationState = ((e->direction + 2) >> 2) & 7) + 0x14);
}

ARM void func_02034d64(Entity *e) {
    if (--e->timer != 0) {
        return;
    }
    e->action = 8;
    VE(e->parent)->unk_7d |= (u8)data_020cf9b8[V(e)->unk_7e];
    EnqueueSFX(0x9e);
}

ARM void func_02034db4(Entity *e) {
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
    if (func_0208de54(func_0208da4c()) == 0) {
        if (data_021348c0.unk_0 == 0) {
            V(e)->unk_64 = data_0212ceb0[*func_02093b5c()].entity;
        }
        if (V(e)->unk_64 == NULL) {
            V(e)->unk_64 = func_02045eb4();
        }
    } else {
        V(e)->unk_64 = func_02045eb4();
    }
    if (V(e)->unk_64 == NULL) {
        return;
    }
    e->direction = func_02084fd0(e, V(e)->unk_64);
    InitAnimationForceUpdate(e, (e->animationState = ((e->direction + 2) >> 2) & 7) + 0x14);
}

ARM void func_02034ea0(Entity *e) {
    if (V(e)->unk_6e & 0x80) {
        e->action = 0xb;
        func_02035a8c(e);
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
        ProcessMovement(e);
    } else {
        e->action = 0xa;
    }
}

ARM void func_02034f74(Entity *e) {
    if (V(e)->unk_6e & 0x80) {
        e->action = 0xb;
        func_02035a8c(e);
        CopyPosition(e->child, e);
        return;
    }
    UpdateAnimationSingleFrame(e);
    if (e->frame & 1) {
        e->frame = 0;
        func_02035f9c(e);
        return;
    }
    if (e->frame & 0x80) {
        e->action = 8;
    }
}

ARM void func_02034fd8(Entity *e) {
    if (V(e)->unk_70 != NULL) {
        UpdateAnimationSingleFrame(V(e)->unk_70);
    }
    UpdateAnimationSingleFrame(e);
    if (!(e->frame & 0x80)) {
        return;
    }
    e->action = 0xc;
    e->timer = 0xf0;
    func_02035c3c(e);
}

ARM void func_02035020(Entity *e) {
    if (e->timer != 0) {
        e->timer--;
        if (func_020358c4(e) == 0) {
            return;
        }
        if (e->health != 0) {
            return;
        }
        func_02035f18(e);
        return;
    }
    if (e->iframes != 0) {
        return;
    }
    e->action = 0xd;
    func_02035c98(e);
}

ARM void func_0203507c(Entity *e) {
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
    func_02035ce8(e);
}

ARM void func_020350cc(Entity *e) {
    ProcessMovement(e);
    if (--e->timer != 0) {
        return;
    }
    e->action = 0xf;
    e->speed = data_020f2680[data_0212c7c8.unk_6 - 1];
    V(e)->unk_6e = 1;
    VE(e->parent)->unk_7d |= (u8)data_020cf9b8[V(e)->unk_7e];
}

ARM void func_02035148(Entity *e) {
    if ((V(e)->unk_6e & 0xc0) == 0xc0) {
        e->action = 0x10;
        func_02035a8c(e);
        func_02035ba4(e);
        CopyPosition(e->child, e);
        return;
    }
    V(e)->unk_6e &= 0x3f;
    func_02035ff8(e);
}

ARM void func_02035194(Entity *e) {
    if (V(e)->unk_70 != NULL) {
        UpdateAnimationSingleFrame(V(e)->unk_70);
    }
    UpdateAnimationSingleFrame(e);
    if (!(e->frame & 0x80)) {
        return;
    }
    e->action = 0x11;
    e->timer = 0xf0;
    func_02035c3c(e);
}

ARM void func_020351dc(Entity *e) {
    if (e->timer != 0) {
        e->timer--;
        if (func_020358c4(e) == 0) {
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
    func_02035c98(e);
}

ARM void func_020352c8(Entity *e) {
    if (V(e)->unk_70 != NULL) {
        UpdateAnimationSingleFrame(V(e)->unk_70);
    }
    UpdateAnimationSingleFrame(e);
    if (!(e->frame & 0x80)) {
        return;
    }
    V(e)->unk_7c = 0x10;
    func_02035ce8(e);
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

ARM void func_02035370(Entity *e) {
    if (e->timer != 0) {
        e->timer--;
        return;
    }
    e->action = 0x14;
    e->timer = 0x78;
    e->speed = 0x120;
    if (func_0208de54(func_0208da4c()) == 0) {
        if (data_021348c0.unk_0 == 0) {
            V(e)->unk_64 = data_0212ceb0[*func_02093b5c()].entity;
        }
        if (V(e)->unk_64 == NULL) {
            V(e)->unk_64 = func_02045eb4();
        }
    } else {
        V(e)->unk_64 = func_02045eb4();
    }
    e->direction = func_02084fd0(e, V(e)->unk_64);
    InitAnimationForceUpdate(e, (e->animationState = ((e->direction + 2) >> 2) & 7) + 0x14);
}

ARM void func_02035438(Entity *e) {
    if ((V(e)->unk_6e & 0xc0) == 0xc0) {
        e->action = 0x10;
        func_02035a8c(e);
        func_02035ba4(e);
        CopyPosition(e->child, e);
        return;
    }
    V(e)->unk_6e &= 0x3f;
    if ((e->contactFlags & 0x80) && e->contactedEntity->type < 4) {
        if (func_0208de54(func_0208da4c()) == 0) {
            if (data_021348c0.unk_0 == 0) {
                V(e)->unk_64 = data_0212ceb0[*func_02093b5c()].entity;
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
        ProcessMovement(e);
    } else {
        e->action = 0x15;
    }
}

ARM void func_02035588(Entity *e) {
    if ((V(e)->unk_6e & 0xc0) == 0xc0) {
        e->action = 0x10;
        func_02035a8c(e);
        func_02035ba4(e);
        CopyPosition(e->child, e);
        return;
    }
    V(e)->unk_6e &= 0x3f;
    UpdateAnimationSingleFrame(e);
    if (e->frame & 1) {
        e->frame = 0;
        func_02035f9c(e);
        return;
    }
    if (e->frame & 0x80) {
        e->action = 0x13;
    }
}

ARM void func_02035600(Entity *e) {
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
    ProcessMovement(e);
}

ARM void func_02035658(Entity *e) {
    e->x.HALF.HI += data_020f2675[e->timer & 3];
    if (++e->timer >= 0x3c) {
        e->timer = 0x1e;
        e->action = 0x18;
    }
}

ARM void func_0203569c(Entity *e) {
    if (--e->timer != 0) {
        return;
    }
    func_02035f18(e);
}

ARM void func_020356bc(Entity *e) {
    e->action = 1;
    e->health = 0xff;
    e->unk_3c &= 0x7f;
    e->unk_3f = 0x3f;
    e->hitbox = data_020d11ac;
}

ARM void func_020356f4(Entity *e) {
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

ARM void func_02035740(Entity *e) {
    if (--e->timer == 0) {
        e->action = 3;
        InitAnimationForceUpdate(e, 9);
    }
    if (!(e->unk_3c & 0x80)) {
        e->action = 1;
    }
}

ARM void func_02035780(Entity *e) {
    e->z.HALF.HI = data_020f2671[(e->frame >> 4) & 3];
    e->parent->z.HALF.HI = e->z.HALF.HI;
    if (e->frame & 1) {
        Entity *proj = CreateProjectile(0xd);
        if (proj != NULL) {
            proj->direction = GetFacingDirection(e, data_0212ceb0[Random() % data_0212c7c8.unk_0].entity);
            CopyPosition(e, proj);
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

ARM void func_02035860(Entity *e, Entity *src) {
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

ARM BOOL func_020358c4(Entity *e) {
    Entity *other = V(e)->unk_70;
    if (other != NULL && other->spriteSettings.b20 == e->spriteSettings.b20) {
        if (e->contactFlags & 0x80) {
            if ((u16)(e->contactFlags - 0x84) <= 0x9f) {
                if (e->spriteSettings.b20 - 7 == e->contactedEntity->type) {
                    func_02035860(e, e);
                    return TRUE;
                }
            } else {
                e->iframes = 0xf8;
                other->iframes = 0xf8;
            }
        } else if (other->contactFlags & 0x80) {
            if ((u16)(other->contactFlags - 0x84) <= 0x9f) {
                if (other->spriteSettings.b20 - 7 == other->contactedEntity->type) {
                    func_02035860(e, other);
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
                func_02035860(e, src);
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
