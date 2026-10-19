#include "engine/functions.h"
#include "enemy/em12.h"
#include "global.h"

// Original names: em12_wakeup, em12_move, em12_return, em12_sleep, em12_kemuriSet, igoalWalk, tgtareacheck (igoalGetDir is in scratch/agentA/nonmatching/func_0203bca4.c)

ARM void em12_wakeup(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if ((e->frame & 0x80) == 0) {
        return;
    }
    e->action = 4;
    e->statusFlags |= 0x80;
    V(e)->w70.b.inArea = 0;
    V(e)->w70.b.flag = 0;
    V(e)->w70.b.walkState = 0;
    e->animationState = 2;
    InitAnimationForceUpdate(e, 2);
    yukaRewCell(e);
}

ARM void em12_move(Entity *e) {
    u8 diff;

    UpdateAnimationSingleFrame(e);
    switch (e->frame & 7) {
    case 1:
        e->frame = 0;
        e->zVelocity = 0x11800;
        igoalGetDir(e);
        if ((((e->direction + 4) & 0x18) >> 3) == e->animationState) {
            V(e)->w70.b.flag = 1;
        } else {
            V(e)->w70.b.flag = 0;
            diff = (e->direction - (e->animationState << 3)) & 0x1f;
            if (diff == 0x10) {
                if (V(e)->w70.b.inArea != 0) {
                    diff = CalculateDirectionTo(e->x.HALF.HI, e->y.HALF.HI, V(e)->homeX, V(e)->homeY);
                } else {
                    diff = func_02084fd0(e, V(e)->target);
                }
                diff = (e->direction - diff) & 0x1f;
            }
            if (diff > 0x10) {
                e->animationState = (e->animationState - 1) & 3;
            } else {
                e->animationState = (e->animationState + 1) & 3;
            }
        }
        e->direction = (e->direction + 4) & 0x18;
        e->x.HALF.LO = 0;
        e->y.HALF.LO = 0;
        EnqueueSFX(0x5d);
        break;
    case 2:
        if (e->frame & 0x80) {
            InitAnimationForceUpdate(e, (e->animationState + 4) & 0xff);
        }
        if (V(e)->w70.b.flag != 0) {
            igoalWalk(e);
        }
        if (UpdateGravity(e, 0x1c00) != 0) {
            return;
        }
        em12_kemuriSet(e);
        EnqueueSFX(0x5e);
        break;
    default:
        if ((e->frame & 0x80) == 0) {
            return;
        }
        InitAnimationForceUpdate(e, e->animationState);
        if ((V(e)->w70.b.inArea & 0x80) == 0) {
            return;
        }
        e->action = 5;
        e->direction = 0x10;
        V(e)->w70.b.flag = 0;
        break;
    }
}

ARM void em12_return(Entity *e) {
    u32 playerIndex;
    Entity *target;
    int diff;

    UpdateAnimationSingleFrame(e);
    playerIndex = (data_0212c5bc & 3) % data_0212c7c8.unk_0;
    target = data_0212ceb0[playerIndex].entity;
    if ((u32)(target->x.HALF.HI - V(e)->areaX) <= V(e)->areaW &&
        (u32)(target->y.HALF.HI - V(e)->areaY) <= V(e)->areaH) {
        if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) != 0) {
            V(e)->target = data_0212ceb0[playerIndex].entity;
        } else {
            V(e)->target = data_0212ceb0[*Knife_Single_SinglePlay_GetInstance()].entity;
        }
        V(e)->w70.b.inArea = 0xff;
    } else {
        V(e)->w70.b.inArea = 0;
    }

    switch (e->frame & 7) {
    case 1:
        e->frame = 0;
        e->zVelocity = 0x11800;
        if (((e->direction + 4) & 0x18) >> 3 != e->animationState) {
            diff = (e->direction - (e->animationState << 3)) & 0x1f;
            if (diff > 0x10) {
                e->animationState = (e->animationState - 1) & 3;
            } else {
                e->animationState = (e->animationState + 1) & 3;
            }
        }
        EnqueueSFX(0x5d);
        break;
    case 2:
        if (e->frame & 0x80) {
            InitAnimationForceUpdate(e, (e->animationState + 4) & 0xff);
        }
        if (UpdateGravity(e, 0x1c00) != 0) {
            return;
        }
        em12_kemuriSet(e);
        EnqueueSFX(0x5e);
        break;
    default:
        if ((e->frame & 0x80) == 0) {
            return;
        }
        InitAnimationForceUpdate(e, e->animationState);
        if (V(e)->w70.b.inArea == 0xff) {
            e->action = 4;
            V(e)->w70.b.inArea = 0;
            V(e)->w70.b.flag = 0;
            V(e)->w70.b.walkState = 0;
            return;
        }
        if ((((e->direction + 4) & 0x18) >> 3) != e->animationState) {
            return;
        }
        e->action = 6;
        e->statusFlags &= 0x7f;
        InitAnimationForceUpdate(e, 0xe);
        igoalRewCell(e);
        break;
    }
}

ARM void em12_sleep(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (e->frame & 0x80) {
        e->action = 2;
        e->spriteSettings.b0 = 0;
    }
}

ARM void em12_kemuriSet(Entity *e) {
    Entity *fx;

    fx = GetSetWork(0xf, 2, 0);
    if (fx != NULL) {
        ObjPosCopy(e, fx);
        fx->x.HALF.HI += em12_kemuriOffsets[e->animationState * 4];
        fx->y.HALF.HI += em12_kemuriOffsets[e->animationState * 4 + 1];
    }
    fx = GetSetWork(0xf, 2, 0);
    if (fx != NULL) {
        ObjPosCopy(e, fx);
        fx->x.HALF.HI += em12_kemuriOffsets[e->animationState * 4 + 2];
        fx->y.HALF.HI += em12_kemuriOffsets[e->animationState * 4 + 3];
    }
}

ARM void igoalWalk(Entity *e) {
    func_02089e34(e, 9, (u16)(e->x.HALF.HI + em12_walkOffsets[e->animationState * 4]),
                  (u16)(e->y.HALF.HI + em12_walkOffsets[e->animationState * 4 + 1]));
    func_02089e34(e, 9, (u16)(e->x.HALF.HI + em12_walkOffsets[e->animationState * 4 + 2]),
                  (u16)(e->y.HALF.HI + em12_walkOffsets[e->animationState * 4 + 3]));
    if (V(e)->w70.b.inArea != 0) {
        u8 snapped = 0;
        if ((u32)(e->x.HALF.HI - (u16)V(e)->homeX + 2) <= 4) {
            e->x.HALF.HI = (u16)V(e)->homeX;
            snapped = 0x80;
        }
        if ((u32)(e->y.HALF.HI - (u16)V(e)->homeY + 2) <= 4) {
            e->y.HALF.HI = (u16)V(e)->homeY;
            V(e)->w70.b.inArea |= (snapped & 0x80);
        }
        if ((V(e)->w70.b.inArea & 0x80) != 0) {
            return;
        }
        if (func_020847a0(e) != 0) {
            return;
        }
        if ((V(e)->w70.b.walkState & 0x80) != 0) {
            V(e)->w70.b.walkState |= 2;
        }
        V(e)->w70.b.walkState |= 1;
    } else {
        func_020847a0(e);
    }
}

ARM BOOL tgtareacheck(Entity *e, Entity *target) {
    if (target == NULL) {
        return FALSE;
    }
    if (data_0212c584[target->type] & 0x1000) {
        return FALSE;
    }
    if (target->health == 0) {
        return FALSE;
    }
    if ((u32)(target->x.HALF.HI - V(e)->areaX) > V(e)->areaW) {
        return FALSE;
    }
    return (u32)(target->y.HALF.HI - V(e)->areaY) <= V(e)->areaH;
}
