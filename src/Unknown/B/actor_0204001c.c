#include "Unknown/B/Actor_0204001c.h"
#include "global.h"

ARM void func_0204001c(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (V(e)->unk_64 == NULL) {
        V(e)->unk_64 = func_02084f98(e, 0x58, 0x58);
    }
    if ((e->frame & 0x20) && V(e)->unk_64 != NULL) {
        func_02040334(e);
        return;
    }
    if (e->frame & 0x80) {
        func_02040304(e);
    }
}

ARM void func_0204007c(Entity *e) {
    if (--e->timer != 0) {
        return;
    }
    e->action = 5;
    e->timer = 0x78;
    e->subtimer = 0x1e;
    e->speed = 0x100;
}

ARM void func_020400b4(Entity *e) {
    if (e->subtimer != 0) {
        e->subtimer--;
    }
    if (e->subtimer == 0 && func_02040368(e)) {
        e->action = 6;
        e->speed = 0x280;
        e->direction = (e->animationState & 3) << 3;
        func_02040254(e, 0x10);
        e->child->unk_44 = 8;
        return;
    }
    e->child->unk_44 = 4;
    e->direction = func_02084fd0(e, V(e)->unk_64);
    func_02040254(e, 8);
    func_020847a0(e);
    UpdateAnimationSingleFrame(e);
    if (--e->timer == 0) {
        func_020402e0(e);
    }
}

ARM void func_0204017c(Entity *e) {
    func_020852f8(e, 0x40, e->direction ^ 0x10);
    UpdateAnimationSingleFrame(e);
    if (e->frame & 0x20) {
        e->action = 7;
    }
}

ARM void func_020401b4(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (e->frame & 0x20) {
        func_020847a0(e);
        func_0204042c(e);
        return;
    }
    if (e->frame & 0x80) {
        func_020402e0(e);
    }
}

ARM void func_020401f4(Entity *e) {
    if (e->child == NULL) {
        return;
    }
    CopyPosition(e, e->child);
    e->child->hitbox = data_020d310c[((e->animationState & 3) << 2) + (e->frame & 3)];
    e->child->unk_3c = (e->child->unk_3c & 0x7f) | (e->unk_3c & 0x80);
}

ARM void func_02040254(Entity *e, u8 a) {
    u8 d = ((e->direction + 4) & 0x18) >> 3;
    if ((e->animationState & 0x1c) == a) {
        if ((e->direction & 7) != 4) {
            if (d == (e->animationState & 3)) {
                return;
            }
            InitAnimationForceUpdate(e, e->animationState = a + d);
            return;
        }
        if (((d - (e->animationState & 3)) & 3) < 2) {
            return;
        }
        InitAnimationForceUpdate(e, e->animationState = a + d);
        return;
    }
    InitAnimationForceUpdate(e, e->animationState = a + d);
}

ARM void func_020402e0(Entity *e) {
    e->action = 1;
    e->timer = 0x3c;
    InitAnimationForceUpdate(e, e->animationState & 3);
}

ARM void func_02040304(Entity *e) {
    e->action = 2;
    e->timer = 0xf0;
    e->subtimer = 1;
    e->speed = 0x80;
    V(e)->unk_64 = NULL;
}

ARM void func_02040334(Entity *e) {
    e->action = 4;
    e->timer = 0xf;
    e->direction = GetFacingDirection(e, V(e)->unk_64);
    func_02040254(e, 0);
}

ARM BOOL func_02040368(Entity *e) {
    if (func_02084ae8(e, 0xc, V(e)->unk_64) & 0x80) {
        switch (e->animationState & 3) {
            case 0:
                if (e->y.HALF.HI - V(e)->unk_64->y.HALF.HI < 0x38) {
                    return TRUE;
                }
                break;
            case 1:
                if (V(e)->unk_64->x.HALF.HI - e->x.HALF.HI < 0x38) {
                    return TRUE;
                }
                break;
            case 2:
                if (V(e)->unk_64->y.HALF.HI - e->y.HALF.HI < 0x38) {
                    return TRUE;
                }
                break;
            case 3:
                if (e->x.HALF.HI - V(e)->unk_64->x.HALF.HI < 0x38) {
                    return TRUE;
                }
                break;
        }
    }
    return FALSE;
}

ARM void func_0204042c(Entity *e) {
    if ((e->unk_28 & 3) != 0) {
        return;
    }
    Entity *other = CreateFx(0xf, 0x11, 0);
    if (other == NULL) {
        return;
    }
    const s8 *p = data_020d2e64 + ((e->animationState & 3) * 2);
    PositionRelative(e, other, (s32)p[0] << 16, (s32)p[1] << 16);
}

ARM void func_0204048c(Entity *e) {
    EnemyFunctionHandler(e, data_020d2fe4);
}

ARM void func_020404a0(Entity *e) {
    data_020d2fb4[e->action](e);
}

ARM void func_020404bc(Entity *e) {
    if (e->action <= 2) {
        e->action = 3;
        func_02040254(e, 0xc);
    }
    GenericKnockback(e, data_020d2fe4);
}
