#include "engine/functions.h"
#include "global.h"
#include "enemy/em20.h"
#include "enemy/em20_7.h"

// Functions in this file: em20_dush (0x0203e9d4), em20_stop (0x0203eacc).

ARM void em20_dush(Entity *e) {
    s32 x;
    s32 y;
    if (func_020847c8(e) == 0) {
        e->action = 6;
        e->speed = 0xe0;
        e->direction ^= 0x10;
        e->zVelocity = 0x18000;
        YureSet(8, 0);
        return;
    }
    UpdateAnimationSingleFrame(e);
    x = e->x.HALF.HI + em20_dushOffsetTable[e->animationState * 4];
    y = e->y.HALF.HI + em20_dushOffsetTable[e->animationState * 4 + 1];
    func_02089e34(e, 9, (u16)x, (u16)y);
    x = e->x.HALF.HI + em20_dushOffsetTable[e->animationState * 4 + 2];
    y = e->y.HALF.HI + em20_dushOffsetTable[e->animationState * 4 + 3];
    func_02089e34(e, 9, (u16)x, (u16)y);
    if (dushCheck(e) != 0) {
        e->action = 5;
    }
}

ARM void em20_stop(Entity *e) {
    s32 x;
    s32 y;
    e->speed -= 0x20;
    if (e->speed >= 0x100) {
        x = e->x.HALF.HI + em20_dushOffsetTable[e->animationState * 4];
        y = e->y.HALF.HI + em20_dushOffsetTable[e->animationState * 4 + 1];
        func_02089e34(e, 9, (u16)x, (u16)y);
        x = e->x.HALF.HI + em20_dushOffsetTable[e->animationState * 4 + 2];
        y = e->y.HALF.HI + em20_dushOffsetTable[e->animationState * 4 + 3];
        func_02089e34(e, 9, (u16)x, (u16)y);
    }
    if (e->speed <= 0) {
        e->action = 1;
        e->timer = 0x10;
        return;
    }
    func_020847c8(e);
    kamen_kemuriSet(e);
}
