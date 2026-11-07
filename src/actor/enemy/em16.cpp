#include "engine/functions.h"
#include "global.h"
#include "actor/enemy/em16.h"
// Actor em16 (module em16), unit 1. Address -> name:
//   0x0203cfcc Em16 (entry, EnemyFunctionHandler on em16_stateTable)
//   0x0203cfe0 em16_normal
// Not matched (best attempts in scratch/agentB/nonmatching): em16_damage 0x0203cffc, em16_getdir 0x0203d1a4,
// em16_move 0x0203d218.

// Entry of the actor: runs the state handler for the current action.
void Em16(Entity *e) {
    EnemyFunctionHandler(e, em16_stateTable);
}

// Runs the handler for the current action.
void em16_normal(Entity *e) {
    em16_actionTable[e->action](e);
}

// em16_damage (0x0203cffc): hit reaction of em16; a hit in action 1 or 2 stops the actor, releases its child and turns it
// away from the hit before the generic knockback runs.
void em16_damage(Entity *e) {
    if (e->action - 1 <= 1 && e->contactFlags > 0x83) {
        e->action = 5;
        e->timer = 0x10;
        if (e->child != NULL) {
            e->child->parent = NULL;
        }
        e->direction = ((e->baseDirection ^ 0x10) + 4) & 0x18;
        e->animationState = e->direction >> 3;
        InitAnimationForceUpdate(e, em16_animTable[e->animationState]);
    }
    GenericKnockback(e, em16_stateTable);
}

// Actor em16 (module em16), unit 2. Address -> name:
//   0x0203d088 em16_init, 0x0203d0cc em16_kyoro, 0x0203d188 em16_wait
// Uses the kyoroSet / frontCheck helpers of unit 3 (declared in wip/B/em16.h).

// Init: sets the sprite priority, the unk_2e value and the hitbox, picks a random direction and starts kyoroSet.
void em16_init(Entity *e) {
    e->spriteSettings.b0 = 1;
    e->unk_2e = 5;
    e->hitbox = em16_hitbox;
    e->direction = Random() & 0x18;
    kyoroSet(e);
}

// Action 2: on animation frame 0 of the walk cycle, a nearby child that is ahead of the actor becomes its target.
// Once the frame bit 0x80 is set, the actor goes to action 2 for 0x1e frames.
void em16_kyoro(Entity *e) {
    Entity *child;

    UpdateAnimationSingleFrame(e);
    if (!frontCheck(e)) {
        return;
    }
    child = FindTargetInRange(e, 0x40, 0x40);
    if (child != NULL) {
        switch (e->animationState) {
        case 0:
            if (child->y.HALF.HI < e->y.HALF.HI) {
                V(e)->target = child;
            }
            break;
        case 1:
            if (child->x.HALF.HI > e->x.HALF.HI) {
                V(e)->target = child;
            }
            break;
        case 2:
            if (child->y.HALF.HI > e->y.HALF.HI) {
                V(e)->target = child;
            }
            break;
        case 3:
            if (child->x.HALF.HI < e->x.HALF.HI) {
                V(e)->target = child;
            }
            break;
        }
    }
    if (e->frame & 0x80) {
        e->action = 2;
        e->timer = 0x1e;
        InitAnimationForceUpdate(e, e->animationState);
    }
}

// Action 3: counts the timer down and goes to action 3 when it runs out.
void em16_wait(Entity *e) {
    e->timer--;
    if (e->timer == 0) {
        e->action = 3;
    }
}
