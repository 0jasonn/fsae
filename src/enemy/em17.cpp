#include "engine/functions.h"
#include "global.h"
#include "enemy/em17.h"
// Actor em17 (module em17), unit 1. Address -> name:
//   0x0203d508 Em17 (entry, EnemyFunctionHandler on em17_stateTable)
//   0x0203d51c em17_normal

// Entry of the actor: runs the state handler for the current action.
ARM void Em17(Entity *e) {
    EnemyFunctionHandler(e, em17_stateTable);
}

// Runs the handler for the current action.
ARM void em17_normal(Entity *e) {
    em17_actionTable[e->action](e);
}

// Knockback: a hit on a lifted object starts the lift-throw (action 4, poseId 0x26) and plays sound 0x238, a hit
// with poseId 0x26 gives invincibility and plays sound 0x60, a hit with poseId 7 plays sound 4.
ARM void em17_damage(Entity *e) {
    if (e->contactFlags != 0x93) {
        if (e->poseId == 0x25 && e->contactFlags >= 0x84) {
            e->action = 4;
            e->zVelocity = 0x10000;
            e->poseId = 0x26;
            e->attackKnockback = 4;
            e->hitbox = em17_hitboxLift;
            e->animationState = 1;
            InitAnimationForceUpdate(e, 1);
            EnqueueSFX(0x238);
        } else if (e->poseId == 0x26 && e->contactFlags != 0x80) {
            e->iframes = 0xfa;
            e->unk_42 = 0x20;
            EnqueueSFX(0x60);
        } else if (e->poseId == 7 && e->contactFlags >= 0x84) {
            EnqueueSFX(4);
        }
    }
    GenericKnockback(e, em17_stateTable);
}
