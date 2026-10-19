#include "enemy/em28.h"
#include "global.h"

// em28_move (0x0204112c): counts down the pause, saves the time spent, then resumes in action 3.
ARM void em28_move(Entity *e) {
    UpdateAnimationSingleFrame(e);
    u8 contact;
    if (--e->timer != 0) {
        contact = func_020847a0(e);
        if (contact != 0) {
            return;
        }
    }
    if (contact == 0) {
        V(e)->restTimer = 0x3c - e->timer;
    }
    e->action = 3;
    e->timer = 0x1e;
}

// em28_wait (0x02041180): steps through the subtimer phases of a turn.
ARM void em28_wait(Entity *e) {
    if (--e->timer != 0) {
        return;
    }
    switch (--e->subtimer) {
        case 0:
            e->action = 1;
            return;
        case 1:
        case 3:
            e->action = 2;
            e->timer = V(e)->restTimer;
            e->direction ^= 0x10;
            e->animationState = e->direction >> 3;
            InitAnimationForceUpdate(e, e->animationState);
            return;
        case 2:
            V(e)->restTimer = 0x3c;
            break;
        default:
            break;
    }
    u8 restTime = V(e)->restTimer;
    e->action = 2;
    e->timer = restTime;
}

// em28_dushInit (0x02041220): after the delay, switches to action 5 at speed 0x120.
ARM void em28_dushInit(Entity *e) {
    if (--e->timer == 0) {
        e->action = 5;
        e->speed = 0x120;
    }
}
