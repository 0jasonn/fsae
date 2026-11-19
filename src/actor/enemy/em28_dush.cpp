#include "engine/functions.h"
#include "actor/enemy/em28_dush.h"
#include "global.h"

// em28_dush (0x02041244): the dash. When a dash direction is found it moves to action 6 and plays the dash pose;
// otherwise, unless the sprite has been stopped, it turns: either straight back, or (first time) towards the target.
void em28_dush(Entity *e) {
    Entity *target;
    u8 startDir;
    int diff;
    if (getDushDir(e) != 0) {
        e->action = 6;
        e->timer = 0x3c;
        InitAnimationForceUpdate(e, e->animationState + 4);
        return;
    }
    if (func_020847a0(e) == 0) {
        if (V(e)->turnActive != 0) {
            e->direction ^= 0x10;
            e->animationState = e->direction >> 3;
            InitAnimationForceUpdate(e, e->animationState);
        } else {
            startDir = e->direction;
            V(e)->turnActive = 1;
            V(e)->turnTimeout = 0x12c;
            target = V(e)->target;
            V(e)->turnStartDir = startDir;
            diff = (func_02086220(target->x.HALF.HI - e->x.HALF.HI, target->y.HALF.HI - e->y.HALF.HI) - startDir * 8) & 0xff;
            if (diff < 0x80) {
                e->direction = (startDir + 8) & 0x18;
            } else {
                e->direction = (startDir - 8) & 0x18;
            }
            InitAnimationForceUpdate(e, e->animationState = e->direction >> 3);
        }
    }
    UpdateAnimationSingleFrame(e);
}
