#include "engine/functions.h"
#include "global.h"
#include "object/set44.h"

// Set44 family (module set44), 0x0206cf74 .. 0x0206d350.
// Address -> name: 0x0206cf74 Set44, 0x0206cf90 set44_init, 0x0206d060 set44_wait,
// 0x0206d154 set44_move, 0x0206d2e0 set44_reset

ARM void Set44(Entity *e) {
    set44Table[e->action](e);
}

ARM void set44_init(Entity *e) {
    if (e->type2 & flagBits[data_0212c7c8.playerCount - 1]) {
        PutObjWork(e);
        return;
    }
    e->action = 1;
    e->speed = 0x80;
    e->spriteSettings.b0 = 1;
    e->hitbox = set44Hitbox;
    nemoto_writecell(e);
    InitAnimationForceUpdate(e, 0);
    if (data_0212c7c8.pickIndex >= 5) {
        GetVGroup(e, set44VgroupTable[bgmIndexTable[data_0212c7c8.pickIndex][data_0212c7c8.unk_48].table[1]]);
    } else {
        GetVGroup(e, set44VgroupIds[data_0212c7c8.pickIndex]);
    }
}

ARM void set44_wait(Entity *e) {
    Vars_NemotoCell *v = VARS(Vars_NemotoCell, e);
    int cellResult;
    int index;

    if (func_02085ccc(e) != 0) {
        return;
    }
    cellResult = func_02083ca8(v->cell, e->layer);
    if (cellResult == 0x4009) {
        return;
    }
    index = cellResult - 0x400a;
    if ((u16)index <= 3) {
        e->direction = (index & 3) << 3;
        e->action = 2;
        e->timer = 0x20;
        EnqueueSFX(0x15);
        nemoto_rewritecell(e);
        cellResult = func_02083ca8((u16)(v->cell + cellDeltaTable[e->direction >> 3]), e->layer);
        if (cellResult == 0x148 || cellResult == 0x14a) {
            e->z.HALF.HI = -2;
        }
        return;
    }
    {
        Entity *found = GetSetWork(0xf, 4, 0);
        if (found != NULL) {
            ObjPosCopy(e, found);
        }
    }
    PutObjWork(e);
}

ARM void set44_move(Entity *e) {
    Vars_NemotoCell *v = VARS(Vars_NemotoCell, e);
    int hitMask;

    MoveDir(e);
    hitMask = func_020862a8(e);
    if (hitMask != 0) {
        if (hitMask & 1) {
            PLAYER_ENTITY(0)->contactFlags = 0xb8;
            func_02089988(data_0212ceb0);
        }
        if (hitMask & 2) {
            PLAYER_ENTITY(1)->contactFlags = 0xb8;
            func_02089988(data_0212ceb0 + 0x94);
        }
        if (hitMask & 4) {
            PLAYER_ENTITY(2)->contactFlags = 0xb8;
            func_02089988(data_0212ceb0 + 0x94 * 2);
        }
        if (hitMask & 8) {
            PLAYER_ENTITY(3)->contactFlags = 0xb8;
            func_02089988(data_0212ceb0 + 0x94 * 3);
        }
    }

    e->timer--;
    if (e->timer != 0) {
        return;
    }
    if (func_02085ccc(e) != 0) {
        return;
    }
    e->z.HALF.HI = 0;
    if (func_02083d28(e) != 0) {
        Entity *found = GetSetWork(0xf, 4, 0);
        if (found != NULL) {
            ObjPosCopy(e, found);
        }
        e->spriteSettings.b0 = 0;
        e->x.HALF.HI += set44MoveOffsets[e->direction >> 2];
        e->y.HALF.HI += set44MoveOffsets[(e->direction >> 2) + 1];
        nemoto_writecell(e);
        func_0208366c(0, v->cell, e->layer);
        e->action = 3;
        e->timer = 0x3c;
    } else {
        e->action = 1;
        nemoto_writecell(e);
    }
}

ARM void set44_reset(Entity *e) {
    Vars_NemotoCell *v = VARS(Vars_NemotoCell, e);

    e->timer--;
    if (e->timer != 0) {
        e->spriteSettings.b0 ^= 1;
        return;
    }
    e->spriteSettings.b0 = 1;
    e->action = 1;
    func_0208366c(0x4009, v->cell, e->layer);
}
