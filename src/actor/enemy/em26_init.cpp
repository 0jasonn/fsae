#include "engine/functions.h"
#include "actor/enemy/em26_init.h"
#include "global.h"

// em26_init (0x020408ac): sets the bubble up; the first time it also records the area box (position and size in
// pixels) it floats in and moves to the cell centre given by type2 / timer.
void em26_init(Entity *e) {
    e->action = 1;
    e->z.HALF.HI = -1;
    e->unk_2e = 3;
    e->spriteSettings.b4 = 1;
    e->hitbox = data_020d31a0;
    V(e)->lifeTimer = 0x384;
    if (V(e)->resetTimer == 0) {
        V(e)->resetVal2 = ((e->x.HALF.HI & 0x3f) << 4) + 0x10;
        V(e)->resetVal3 = ((e->y.HALF.HI & 0x3f) << 4) + 0x10;
        V(e)->resetVal0 = data_0213492c[e->areaIndex * 2] + ((e->x.HALF.HI & 0xfc0) >> 2);
        V(e)->resetVal1 = em12_spawnOffsetY[e->areaIndex * 2] + ((e->y.HALF.HI & 0xfc0) >> 2);
        e->x.HALF.HI = e->type2 * 16 + 8 + data_0213492c[e->areaIndex * 2];
        e->y.HALF.HI = e->timer * 16 + 8 + em12_spawnOffsetY[e->areaIndex * 2];
        func_0208ae30(e);
    }
    V(e)->homeX = e->x.HALF.HI;
    V(e)->homeY = e->y.HALF.HI;
    InitAnimationForceUpdate(e, 0);
}

// em26_wait (0x020409b0): counts the reset timer down; then, once a player (picked by the frame counter in a
// wireless game) with a live health stands inside the area box on the same layer, the bubble catches it.
void em26_wait(Entity *e) {
    Entity *target;
    if (V(e)->resetTimer != 0) {
        V(e)->resetTimer--;
        return;
    }
    if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) == 0) {
        target = playerWork[*Knife_Single_SinglePlay_GetInstance()].entity;
    } else {
        target = playerWork[frameCounter.frame & 3].entity;
    }
    if (target == NULL) {
        return;
    }
    if ((u32)(target->x.HALF.HI - V(e)->resetVal0) > V(e)->resetVal2 ||
        (u32)(target->y.HALF.HI - V(e)->resetVal1) > V(e)->resetVal3) {
        return;
    }
    if ((target->layer & e->layer) == 0 || target->health == 0) {
        return;
    }
    if (playerKeysPrev[target->type] & 0x1000) {
        return;
    }
    V(e)->unk_64 = target;
    e->action = 2;
    e->spriteSettings.b0 = 1;
    e->statusFlags |= 0x80;
    e->direction = GetFacingDirection(e, target);
    e->zVelocity = 0x24000;
    target = GetSetWork(0xf, 0xc, 0);
    if (target != NULL) {
        ObjPosCopy(e, target);
    }
}
