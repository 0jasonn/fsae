#include "Unknown/B/Actor_0204001c.h"
#include "global.h"

ARM void func_02040548(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (V(e)->unk_64->health == 0) {
        e->timer = 1;
    }
    u8 v = ((func_02084fd0(e, V(e)->unk_64) + 4) & 0x18) >> 3;
    if ((e->animationState & 3) != v) {
        e->timer = 1;
    }
    func_02040674(e);
    if ((u16)(e->x.HALF.HI - V(e)->unk_7c + 2) > 4 || (u16)(e->y.HALF.HI - V(e)->unk_7e + 2) > 4) {
        e->direction = CalculateDirectionTo(e->x.HALF.HI, e->y.HALF.HI, V(e)->unk_7c, V(e)->unk_7e);
        func_020847a0(e);
    }
    if (e->subtimer != 0) {
        e->subtimer--;
    }
    if (e->subtimer == 0 && (e->frame & 1)) {
        if (func_02040708(e)) {
            func_02040744(e);
        }
    }
    if (e->child != NULL) {
        func_02040790(e);
    }
    if (--e->timer == 0) {
        func_020402e0(e);
    }
}

ARM void func_02040674(Entity *e) {
    switch (e->animationState & 3) {
        case 0:
            V(e)->unk_7c = V(e)->unk_64->x.HALF.HI;
            V(e)->unk_7e = V(e)->unk_64->y.HALF.HI + 0x38;
            break;
        case 1:
            V(e)->unk_7c = V(e)->unk_64->x.HALF.HI - 0x38;
            V(e)->unk_7e = V(e)->unk_64->y.HALF.HI;
            break;
        case 2:
            V(e)->unk_7c = V(e)->unk_64->x.HALF.HI;
            V(e)->unk_7e = V(e)->unk_64->y.HALF.HI - 0x38;
            break;
        case 3:
            V(e)->unk_7c = V(e)->unk_64->x.HALF.HI + 0x38;
            V(e)->unk_7e = V(e)->unk_64->y.HALF.HI;
            break;
    }
}

ARM BOOL func_02040708(Entity *e) {
    int r = func_02084ac0(e, 0xc, V(e)->unk_64);
    if (r & 0x80) {
        if ((e->animationState & 3) == ((r & 0x18) >> 3)) {
            return TRUE;
        }
    }
    return FALSE;
}

ARM void func_02040744(Entity *e) {
    Entity *child = CreateProjectile(8);
    if (child == NULL) {
        return;
    }
    child->direction = (e->animationState & 3) << 3;
    child->unk_5e.b0 = 3;
    child->parent = e;
    e->frame = 0;
    e->child = child;
}

ARM void func_02040790(Entity *e) {
    const s8 *p = data_020d2e3c + ((e->animationState & 3) * 2);
    PositionRelative(e, e->child, (s32)p[0] << 16, (s32)p[1] << 16);
}
