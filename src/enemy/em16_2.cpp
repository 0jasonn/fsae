#include "engine/functions.h"
#include "global.h"
#include "enemy/em16.h"
// Actor em16 (module em16), unit 2. Address -> name:
//   0x0203d088 em16_init, 0x0203d0cc em16_kyoro, 0x0203d188 em16_wait
// Uses the kyoroSet / frontCheck helpers of unit 3 (declared in wip/B/em16.h).

// Init: sets the sprite priority, the unk_2e value and the hitbox, picks a random direction and starts kyoroSet.
ARM void em16_init(Entity *e) {
    e->spriteSettings.b0 = 1;
    e->unk_2e = 5;
    e->hitbox = em16_hitbox;
    e->direction = Random() & 0x18;
    kyoroSet(e);
}

// Action 2: on animation frame 0 of the walk cycle, a nearby child that is ahead of the actor becomes its target.
// Once the frame bit 0x80 is set, the actor goes to action 2 for 0x1e frames.
ARM void em16_kyoro(Entity *e) {
    Entity *child;

    UpdateAnimationSingleFrame(e);
    if (!frontCheck(e)) {
        return;
    }
    child = func_02084f98(e, 0x40, 0x40);
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
ARM void em16_wait(Entity *e) {
    e->timer--;
    if (e->timer == 0) {
        e->action = 3;
    }
}
