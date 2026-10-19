#include "engine/functions.h"
#include "enemy/em13.h"
#include "global.h"

ARM void em13_getnextpos(Entity *e) {
    if (!em13_getpos(e)) {
        return;
    }
    e->action = 2;
    e->timer = 0x11;
    e->x.HALF.HI = V(e)->warpX;
    e->y.HALF.HI = V(e)->warpY;
    func_0208ae30(e);
}

ARM void em13_search(Entity *e) {
    e->timer--;
    if (e->timer != 0) {
        Entity *child = func_02084f98(e, 0x60, 0x40);
        if (child == NULL) {
            return;
        }
        u8 facing = GetFacingDirection(e, child);
        s32 direction = (facing + 4) & 0x18;
        e->direction = direction;
        e->animationState = e->direction >> 3;
        e->action = 3;
        e->timer = 0x10;
        InitAnimationForceUpdate(e, e->animationState);
        func_02085f98(e, 0x5c);
    } else {
        e->action = 1;
    }
}

ARM void em13_appear(Entity *e) {
    WizWarpAppear(e);
    if (e->timer != 0) {
        return;
    }
    e->action = 4;
    e->timer = 0x10;
    e->statusFlags |= 0x80;
}

ARM void em13_move(Entity *e) {
    if (--e->timer != 0) {
        return;
    }
    Entity *tama = GetTamaWork(5);
    if (tama == NULL) {
        e->timer++;
        return;
    }
    tama->type = e->type;
    tama->direction = e->direction;
    tama->parent = e;
    e->child = tama;
    e->action = 5;
    e->timer = 0x3c;
    InitAnimationForceUpdate(e, (e->animationState + 4) & 0xff);
}

ARM void em13_attack(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (--e->timer != 0) {
        return;
    }
    e->action = 6;
    WizVanishInit(e);
}

ARM void em13_vanish(Entity *e) {
    WizWarpVanish(e);
    if (e->timer != 0) {
        return;
    }
    e->action = 7;
    V(e)->waitTimer = V(e)->waitFrames;
    e->spriteSettings.b0 = 0;
}

ARM void em13_wait(Entity *e) {
    V(e)->waitTimer--;
    if (V(e)->waitTimer != 0) {
        return;
    }
    nextMove(e);
}
