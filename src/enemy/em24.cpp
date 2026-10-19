#include "engine/functions.h"
#include "enemy/em24.h"
#include "global.h"

ARM void em24_fugofugo(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (V(e)->aimTarget == NULL) {
        V(e)->aimTarget = func_02084f98(e, 0x58, 0x58);
    }
    if ((e->frame & 0x20) && V(e)->aimTarget != NULL) {
        aimSet(e);
        return;
    }
    if (e->frame & 0x80) {
        moveSet(e);
    }
}

ARM void em24_aimInit(Entity *e) {
    if (--e->timer != 0) {
        return;
    }
    e->action = 5;
    e->timer = 0x78;
    e->subtimer = 0x1e;
    e->speed = 0x100;
}

ARM void em24_aimMove(Entity *e) {
    if (e->subtimer != 0) {
        e->subtimer--;
    }
    if (e->subtimer == 0 && em24_crossCheck(e)) {
        e->action = 6;
        e->speed = 0x280;
        e->direction = (e->animationState & 3) << 3;
        charset(e, 0x10);
        e->child->unk_44 = 8;
        return;
    }
    e->child->unk_44 = 4;
    e->direction = func_02084fd0(e, V(e)->aimTarget);
    charset(e, 8);
    func_020847a0(e);
    UpdateAnimationSingleFrame(e);
    if (--e->timer == 0) {
        em24_waitSet(e);
    }
}

ARM void em24_attackInit(Entity *e) {
    func_020852f8(e, 0x40, e->direction ^ 0x10);
    UpdateAnimationSingleFrame(e);
    if (e->frame & 0x20) {
        e->action = 7;
    }
}

ARM void em24_attack(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (e->frame & 0x20) {
        func_020847a0(e);
        em24_kemuriSet(e);
        return;
    }
    if (e->frame & 0x80) {
        em24_waitSet(e);
    }
}

ARM void swordset(Entity *e) {
    if (e->child == NULL) {
        return;
    }
    ObjPosCopy(e, e->child);
    e->child->hitbox = em24_swordHitboxes[((e->animationState & 3) << 2) + (e->frame & 3)];
    e->child->unk_3c = (e->child->unk_3c & 0x7f) | (e->unk_3c & 0x80);
}

ARM void charset(Entity *e, u8 baseAnim) {
    u8 facing = ((e->direction + 4) & 0x18) >> 3;
    if ((e->animationState & 0x1c) == baseAnim) {
        if ((e->direction & 7) != 4) {
            if (facing == (e->animationState & 3)) {
                return;
            }
            InitAnimationForceUpdate(e, e->animationState = baseAnim + facing);
            return;
        }
        if (((facing - (e->animationState & 3)) & 3) < 2) {
            return;
        }
        InitAnimationForceUpdate(e, e->animationState = baseAnim + facing);
        return;
    }
    InitAnimationForceUpdate(e, e->animationState = baseAnim + facing);
}

ARM void em24_waitSet(Entity *e) {
    e->action = 1;
    e->timer = 0x3c;
    InitAnimationForceUpdate(e, e->animationState & 3);
}

ARM void moveSet(Entity *e) {
    e->action = 2;
    e->timer = 0xf0;
    e->subtimer = 1;
    e->speed = 0x80;
    V(e)->aimTarget = NULL;
}

ARM void aimSet(Entity *e) {
    e->action = 4;
    e->timer = 0xf;
    e->direction = GetFacingDirection(e, V(e)->aimTarget);
    charset(e, 0);
}

ARM BOOL em24_crossCheck(Entity *e) {
    if (func_02084ae8(e, 0xc, V(e)->aimTarget) & 0x80) {
        switch (e->animationState & 3) {
            case 0:
                if (e->y.HALF.HI - V(e)->aimTarget->y.HALF.HI < 0x38) {
                    return TRUE;
                }
                break;
            case 1:
                if (V(e)->aimTarget->x.HALF.HI - e->x.HALF.HI < 0x38) {
                    return TRUE;
                }
                break;
            case 2:
                if (V(e)->aimTarget->y.HALF.HI - e->y.HALF.HI < 0x38) {
                    return TRUE;
                }
                break;
            case 3:
                if (e->x.HALF.HI - V(e)->aimTarget->x.HALF.HI < 0x38) {
                    return TRUE;
                }
                break;
        }
    }
    return FALSE;
}

ARM void em24_kemuriSet(Entity *e) {
    if ((e->unk_28 & 3) != 0) {
        return;
    }
    Entity *smoke = GetSetWork(0xf, 0x11, 0);
    if (smoke == NULL) {
        return;
    }
    const s8 *offset = em24_smokeOffsets + ((e->animationState & 3) * 2);
    ObjPosCopyOfs32(e, smoke, (s32)offset[0] << 16, (s32)offset[1] << 16);
}

ARM void func_0204048c(Entity *e) {
    EnemyFunctionHandler(e, em24_stateTable);
}

ARM void em25_normal(Entity *e) {
    em25_stateTable[e->action](e);
}

ARM void em25_damage(Entity *e) {
    if (e->action <= 2) {
        e->action = 3;
        charset(e, 0xc);
    }
    GenericKnockback(e, em24_stateTable);
}
