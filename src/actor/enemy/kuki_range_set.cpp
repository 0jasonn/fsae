#include "engine/functions.h"
#include "actor/enemy/em2c.h"

// kukiRangeSet (0x0203464c): moves e towards target by `speed` (at least 4) along the angle between them, one axis at a
// time; on an axis where the remaining distance is not larger than the step, e lands exactly on the target.
// The absolute values are taken in place (step first) and the locals are declared in this order: both decide which of
// the two dying position registers the difference gets.
void kukiRangeSet(Entity *e, Entity *target, u16 speed) {
    u8 angle;
    s32 diffY;
    s32 stepY;
    s32 diffX;
    s32 stepX;
    s32 moveX;
    s32 moveY;

    angle = func_02086220(target->x.HALF.HI - e->x.HALF.HI, target->y.HALF.HI - e->y.HALF.HI);
    if (speed < 4) {
        speed = 4;
    }
    diffX = target->x.WORD - e->x.WORD;
    stepX = (speed * trigTable[angle]) << 8;
    moveX = diffX - stepX;
    if (stepX < 0) {
        stepX = -stepX;
    }
    if (diffX < 0) {
        diffX = -diffX;
    }
    if (diffX - stepX <= 0) {
        moveX = 0;
    }
    e->x.WORD += moveX;
    diffY = target->y.WORD - e->y.WORD;
    stepY = -((speed * trigTable[angle + 0x40]) << 8);
    moveY = diffY - stepY;
    if (stepY < 0) {
        stepY = -stepY;
    }
    if (diffY < 0) {
        diffY = -diffY;
    }
    if (diffY - stepY <= 0) {
        moveY = 0;
    }
    e->y.WORD += moveY;
}
