#include "engine/functions.h"
#include "global.h"
#include "actor/enemy/em17_3.h"
#include "engine/player.h"
#include "actor/enemy/em17.h"

// Functions in this file: em17_ball (0x0203daac), em17_standup (0x0203dad4).

void em17_ball(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (buruburu(e) != 0) {
        func_02089524(e);
    }
}

void em17_standup(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (e->frame & 0x80) {
        e->action = 1;
        e->timer = 1;
        e->animationState = 0;
        InitAnimationForceUpdate(e, 0);
    }
}

// Actor em17 (module em17), unit 5. Address -> name:
//   0x0203db0c buruburu

// Horizontal offset added to the actor while it shakes, indexed by (shake timer & 6) >> 1.
extern const s8 em17_shakeOffsetTable[];

// Shaking step: counts the shake timer down. When it runs out the actor stops (action 7, unless the player of its type
// is still in the lift state) and returns 0. While it shakes, the timer at 0x3c sets the flag 2 and odd timer values
// below 0x3c move the actor sideways. Returns 1 while the actor is still shaking.
int buruburu(Entity *e) {
    V(e)->field70.shakeTimer--;
    if (V(e)->field70.shakeTimer == 0) {
        if (e->action == 2 && data_0212ceb0[e->type2].unk_02 != 0) {
            V(e)->field70.shakeTimer = 4;
        } else {
            e->action = 7;
            e->unk_1a = 0;
            e->statusFlags |= 0x80;
            e->poseId = 0x25;
            e->attackKnockback = 0xc;
            e->hitbox = em17_hitboxLift;
            e->animationState = 7;
            InitAnimationForceUpdate(e, 7);
            e->unk_2e = 5;
            return 0;
        }
    } else {
        if (V(e)->field70.shakeTimer == 0x3c) {
            e->unk_1a = 2;
        }
        if ((V(e)->field70.shakeTimer < 0x3c) & (V(e)->field70.shakeTimer & 1)) {
            e->x.HALF.HI += em17_shakeOffsetTable[(V(e)->field70.shakeTimer & 6) >> 1];
        }
    }
    return 1;
}
