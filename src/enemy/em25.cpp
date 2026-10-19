#include "engine/functions.h"
#include "enemy/em24.h"
#include "global.h"

ARM void em25_aimMove(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (V(e)->aimTarget->health == 0) {
        e->timer = 1;
    }
    u8 aimDir = ((func_02084fd0(e, V(e)->aimTarget) + 4) & 0x18) >> 3;
    if ((e->animationState & 3) != aimDir) {
        e->timer = 1;
    }
    getAimPos(e);
    if ((u16)(e->x.HALF.HI - V(e)->aimX + 2) > 4 || (u16)(e->y.HALF.HI - V(e)->aimY + 2) > 4) {
        e->direction = CalculateDirectionTo(e->x.HALF.HI, e->y.HALF.HI, V(e)->aimX, V(e)->aimY);
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
            V(e)->aimX = V(e)->aimTarget->x.HALF.HI;
            V(e)->aimY = V(e)->aimTarget->y.HALF.HI + 0x38;
            break;
        case 1:
            V(e)->aimX = V(e)->aimTarget->x.HALF.HI - 0x38;
            V(e)->aimY = V(e)->aimTarget->y.HALF.HI;
            break;
        case 2:
            V(e)->aimX = V(e)->aimTarget->x.HALF.HI;
            V(e)->aimY = V(e)->aimTarget->y.HALF.HI - 0x38;
            break;
        case 3:
            V(e)->aimX = V(e)->aimTarget->x.HALF.HI + 0x38;
            V(e)->aimY = V(e)->aimTarget->y.HALF.HI;
            break;
    }
}

ARM BOOL crossCheck2(Entity *e) {
    int hitInfo = func_02084ac0(e, 0xc, V(e)->aimTarget);
    if (hitInfo & 0x80) {
        if ((e->animationState & 3) == ((hitInfo & 0x18) >> 3)) {
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
    const s8 *offset = em24_arrowOffsets + ((e->animationState & 3) * 2);
    ObjPosCopyOfs32(e, e->child, (s32)offset[0] << 16, (s32)offset[1] << 16);
}
