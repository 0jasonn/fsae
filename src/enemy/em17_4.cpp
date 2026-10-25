#include "engine/functions.h"
#include "global.h"
#include "enemy/em17.h"
// Actor em17 (module em17), unit 4. Address -> name:
//   0x0203d8f0 em17_batabata, 0x0203d9c4 em17_jump (em17_fall at 0x0203da28 parked, scratch/agentB/nonmatching)

// Wall mask per direction group (direction >> 3), tested against the wall flags.
extern const u16 em17_wallMaskTable[];

// Batabata: a wall hit while the actor is in the air takes it to the lift pose, otherwise it falls with gravity (the
// fall stops at zero height, then the actor is walking again on the ground with its normal hitbox).
ARM void em17_batabata(Entity *e) {
    func_020847c8(e);
    UpdateAnimationSingleFrame(e);
    if (e->wallFlags & em17_wallMaskTable[e->direction >> 3]) {
        V(e)->field70.liftFlag = 1;
        e->poseId = 0x26;
        e->attackKnockback = 4;
        e->animationState = 5;
        InitAnimationForceUpdate(e, 5);
    }
    if (V(e)->field70.liftFlag == 0) {
        e->z.WORD += 0x4000;
    } else {
        UpdateGravity(e, 0x1800);
    }
    if (e->z.HALF.HI != 0) {
        return;
    }
    e->action = 1;
    e->timer = 1;
    e->speed = 0x100;
    e->poseId = 0x25;
    e->attackKnockback = 0xc;
    e->hitbox = em17_hitbox;
    e->animationState = 0;
    InitAnimationForceUpdate(e, 0);
}

// Jump: starts the jump animation with a height of -4 when it is not playing, applies gravity, and switches to the
// landing animation when the vertical speed turns negative.
ARM void em17_jump(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (e->animationState != 2) {
        e->z.HALF.HI = -4;
        e->animationState = 2;
        InitAnimationForceUpdate(e, 2);
    }
    UpdateGravity(e, 0x1800);
    if (e->zVelocity < 0) {
        e->action = 5;
        e->animationState = 3;
        InitAnimationForceUpdate(e, 3);
    }
}
