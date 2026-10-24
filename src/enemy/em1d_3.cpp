#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Functions in this file (actor em1d, original names from the debug build):
//   em1d_aimmove, em1d_rndmove

void seqset(Entity *e, int baseAnim);      // original seqset(OBJ_WORK_*, int)

// Aimmove: counts the timer; every 8th frame turns the entity towards its target; ends the action when the timer runs out.
ARM void em1d_aimmove(Entity *e) {
    e->timer -= 1;
    if ((u8)e->timer != 0) {
        if ((e->timer & 7) == 0) {
            func_02086200(e, func_02084fd0(e, e->child));
        }
        seqset(e, 2);
    } else {
        e->action = 1;
    }
    if (func_020847f8(e) != 0) {
        seqset(e, 2);
    }
    UpdateAnimationSingleFrame(e);
}

// Rndmove: walks in a random direction for the sub timer, then changes the direction and animation at random.
ARM void em1d_rndmove(Entity *e) {
    e->timer -= 1;
    if ((u8)e->timer != 0) {
        e->subtimer -= 1;
        if ((u8)e->subtimer == 0) {
            e->subtimer = 0x2d;
            e->direction = Random() & 0x1f;
            seqset(e, 0);
        }
    } else {
        e->action = 1;
    }
    if (func_020847f8(e) != 0) {
        seqset(e, 0);
    }
    UpdateAnimationSingleFrame(e);
    if ((e->frame & 1) == 0) {
        return;
    }
    if ((Random() & 3) == 0) {
        return;
    }
    InitAnimationForceUpdate(e, e->animationState);
}
