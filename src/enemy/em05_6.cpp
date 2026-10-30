#include "engine/functions.h"
#include "global.h"

// em05_move1 (0x02038f3c): em05 walks in one direction for a while, then turns to a target found by func_02084f98
ARM void em05_move1(Entity *e) {
    Entity *target;
    u8 facing;

    target = 0;
    if (e->subtimer != 0) {
        e->subtimer--;
    } else {
        target = func_02084f98(e, 0x40, 0x30);
    }
    if (target != 0) {
        e->action = 4;
        e->direction = GetFacingDirection(e, target);
        e->zVelocity = 0x1c000;
        e->speed = 0x180;
        e->statusFlags = e->statusFlags | 0x10;
        e->poseId = 6;
        facing = EmCharDir2(e->direction);
        if (facing != 0xff) {
            e->animationState = facing;
        }
        InitAnimationForceUpdate(e, (u8)(e->animationState + 4));
        EnqueueSFX(0x31);
        return;
    }
    e->timer--;
    if (e->timer == 0) {
        e->timer = (Random() & 0x1c) + 0x1e;
        em05DirChange(e);
    }
    func_020847a0(e);
    UpdateAnimationSingleFrame(e);
}
