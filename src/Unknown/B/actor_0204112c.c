#include "Unknown/B/Actor_0204112c.h"
#include "global.h"

ARM void func_0204112c(Entity *e) {
    UpdateAnimationSingleFrame(e);
    u8 r;
    if (--e->timer != 0) {
        r = func_020847a0(e);
        if (r != 0) {
            return;
        }
    }
    if (r == 0) {
        V(e)->unk_74 = 0x3c - e->timer;
    }
    e->action = 3;
    e->timer = 0x1e;
}

ARM void func_02041180(Entity *e) {
    if (--e->timer != 0) {
        return;
    }
    int t = e->subtimer - 1;
    e->subtimer = t;
    switch ((u8)t) {
        case 0:
            e->action = 1;
            return;
        case 1:
        case 3: {
            int d = e->direction ^ 0x10;
            int s = (u8)d >> 3;
            e->action = 2;
            e->timer = V(e)->unk_74;
            e->direction = d;
            e->animationState = s;
            InitAnimationForceUpdate(e, (u8)s);
            return;
        }
        case 2:
            V(e)->unk_74 = 0x3c;
            break;
        default:
            break;
    }
    e->action = 2;
    e->timer = V(e)->unk_74;
}

ARM void func_02041220(Entity *e) {
    if (--e->timer == 0) {
        e->action = 5;
        e->speed = 0x120;
    }
}

ARM void func_02041244(Entity *e) {
    if (func_020415f4(e) != 0) {
        e->action = 6;
        e->timer = 0x3c;
        InitAnimationForceUpdate(e, e->animationState + 4);
        return;
    }
    if (func_020847a0(e) == 0) {
        if (V(e)->unk_75 != 0) {
            e->direction ^= 0x10;
        } else {
            u8 d = e->direction;
            V(e)->unk_78 = 0x12c;
            V(e)->unk_75 = 1;
            V(e)->unk_76 = d;
            Entity *target = V(e)->unk_64;
            u8 a = func_02086220(target->x.HALF.HI - e->x.HALF.HI, target->y.HALF.HI - e->y.HALF.HI);
            a = a - (d << 3);
            u8 nd = (a < 0x80) ? d + 8 : d - 8;
            e->direction = nd & 0x18;
        }
        e->animationState = e->direction >> 3;
        InitAnimationForceUpdate(e, e->animationState);
    }
    UpdateAnimationSingleFrame(e);
}

ARM void func_02041344(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (e->frame & 0x80) {
        e->action = 7;
        InitAnimationForceUpdate(e, e->animationState);
        return;
    }
    if (e->frame != 0) {
        e->unk_3f = 0x3c;
    } else {
        e->unk_3f = 0x3b;
    }
}

ARM void func_0204138c(Entity *e) {
    if (--e->timer != 0) {
        return;
    }
    e->action = 1;
    e->speed = 0x100;
    V(e)->unk_7a = 0x3c;
}

ARM Entity *func_020413bc(Entity *e) {
    Entity *r4 = func_02084f98(e, 0x68, 0x40);
    if (r4 == NULL) {
        return NULL;
    }
    if (func_0208de54(func_0208da4c()) == 0) {
        if (r4 != data_0212ceb0[*func_02093b5c()].unk_28) {
            return NULL;
        }
        if (data_021348cc.unk_0 != 0) {
            return NULL;
        }
    }
    if (data_0212ceb0[r4->type].unk_36 & 0x1091) {
        return NULL;
    }
    return r4;
}

ARM void func_02041458(Entity *e, Entity *target) {
    e->action = 4;
    e->timer = 8;
    V(e)->unk_64 = target;
    int d = GetFacingDirection(e, target);
    e->direction = d;
    e->animationState = (u8)d >> 3;
    InitAnimationForceUpdate(e, e->animationState);
}
