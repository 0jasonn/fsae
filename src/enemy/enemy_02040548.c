#include "enemy/actor_0204001c.h"
#include "global.h"

ARM void em25_aimMove(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (V(e)->unk_64->health == 0) {
        e->timer = 1;
    }
    u8 v = ((func_02084fd0(e, V(e)->unk_64) + 4) & 0x18) >> 3;
    if ((e->animationState & 3) != v) {
        e->timer = 1;
    }
    getAimPos(e);
    if ((u16)(e->x.HALF.HI - V(e)->unk_7c + 2) > 4 || (u16)(e->y.HALF.HI - V(e)->unk_7e + 2) > 4) {
        e->direction = CalculateDirectionTo(e->x.HALF.HI, e->y.HALF.HI, V(e)->unk_7c, V(e)->unk_7e);
        func_020847a0(e);
    }
    if (e->subtimer != 0) {
        e->subtimer--;
    }
    if (e->subtimer == 0 && (e->frame & 1)) {
        if (crossCheck2(e)) {
            arrowSet(e);
        }
    }
    if (e->child != NULL) {
        arrowPosSet(e);
    }
    if (--e->timer == 0) {
        em24_waitSet(e);
    }
}

ARM void getAimPos(Entity *e) {
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

ARM BOOL crossCheck2(Entity *e) {
    int r = func_02084ac0(e, 0xc, V(e)->unk_64);
    if (r & 0x80) {
        if ((e->animationState & 3) == ((r & 0x18) >> 3)) {
            return TRUE;
        }
    }
    return FALSE;
}

ARM void arrowSet(Entity *e) {
    Entity *child = GetTamaWork(8);
    if (child == NULL) {
        return;
    }
    child->direction = (e->animationState & 3) << 3;
    child->unk_5e.b0 = 3;
    child->parent = e;
    e->frame = 0;
    e->child = child;
}

ARM void arrowPosSet(Entity *e) {
    const s8 *p = data_020d2e3c + ((e->animationState & 3) * 2);
    ObjPosCopyOfs32(e, e->child, (s32)p[0] << 16, (s32)p[1] << 16);
}
