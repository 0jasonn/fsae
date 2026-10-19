#include "engine/functions.h"
#include "enemy/em13.h"
#include "global.h"

ARM void WizWarpVanish(Entity *e) {
    u8 timer = --e->timer;
    if (e->animationState & 1) {
        e->y.HALF.HI = (u16)(V(e)->warpY + wizWarpOffsets[15 - timer]);
    } else {
        e->x.HALF.HI = (u16)(V(e)->warpX + wizWarpOffsets[15 - timer]);
    }
}

ARM void WizWarpAppear(Entity *e) {
    u8 timer = --e->timer;
    if (timer != 0) {
        e->spriteSettings.b0 = 1;
        if (e->animationState & 1) {
            e->y.HALF.HI = (u16)(V(e)->warpY + wizWarpOffsets[timer]);
        } else {
            e->x.HALF.HI = (u16)(V(e)->warpX + wizWarpOffsets[timer]);
        }
    } else {
        e->x.HALF.HI = V(e)->warpX;
        e->y.HALF.HI = V(e)->warpY;
    }
}

ARM void WizVanishInit(Entity *e) {
    e->timer = 0x10;
    e->statusFlags &= 0x7f;
    V(e)->warpX = e->x.HALF.HI;
    V(e)->warpY = e->y.HALF.HI;
    EnqueueSFX(0x5c);
}

ARM void nextMove(Entity *e) {
    if (V(e)->subX == 0 && V(e)->subY == 0) {
        Entity *target = data_0212ceb0[Random() % data_0212c7c8.unk_0].entity;
        e->x.HALF.HI = target->x.HALF.HI;
        e->y.HALF.HI = target->y.HALF.HI;
    }
    e->action = 1;
}
