#include "engine/functions.h"
#include "global.h"
#include "object/heart_lift.h"

// heart_lift family (module heart_lift), 0x0206bf28 .. 0x0206c068.
// Address -> name: 0x0206bf28 heart_lift_move (original lift_move), 0x0206c02c heart_lift_end (original lift_end)

ARM void heart_lift_move(Entity *e) {
    Vars_HeartLift *v = VARS(Vars_HeartLift, e);
    Entity *player = data_0212ceb0[e->type2].entity;
    u16 x;
    u16 y;
    int blocked;

    if (v->phase == 0) {
        if (player->animationState == e->type * 2) {
            x = e->x.HALF.HI + heartLiftOffsetTable[player->animationState];
            y = e->y.HALF.HI + heartLiftOffsetTable[player->animationState + 1];
            blocked = func_02083d30(x, y, player->layer);
            if (blocked == 0 || (u8)(blocked - 0xf) >= 0x11) {
                player->x.HALF.HI = x;
                player->y.HALF.HI = y;
            }
        }
        v->phase = 1;
        e->subtimer = 2;
    }
    if ((player->animationState >> 1) != e->type) {
        return;
    }
    if (player->frame == 0) {
        return;
    }
    nemoto_leverMove(e);
    if (v->phase == 1) {
        v->phase = 2;
        EnqueueSFX(0xa4);
    }
}

ARM void heart_lift_end(Entity *e) {
    Vars_HeartLift *v = VARS(Vars_HeartLift, e);

    v->phase = 0;
    if (v->holdTimer == 0) {
        e->action--;
        return;
    }
    func_02089524(e);
    v->holdTimer--;
}
