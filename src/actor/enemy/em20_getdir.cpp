#include "engine/functions.h"
#include "global.h"
#include "actor/enemy/em20_getdir.h"

// Functions in this file: em20_getdir (0x0203e8bc).

void em20_getdir(Entity *e) {
    u32 bits;
    int newDir;

    if (e->timer == 0) {
        bits = func_02084ac8(e, 0x10);
        if ((bits & 0x80) != 0) {
            e->action = 2;
            e->direction = bits & 0x18;
            e->animationState = e->direction >> 3;
            InitAnimationForceUpdate(e, e->animationState);
            return;
        }
        newDir = Random() & 0x18;
        if ((u8)newDir == e->direction) {
            return;
        }
        e->action = 2;
        e->direction = newDir;
        e->animationState = e->direction >> 3;
        InitAnimationForceUpdate(e, e->animationState);
    } else {
        e->timer--;
    }
}
