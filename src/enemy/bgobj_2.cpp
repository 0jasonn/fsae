#include "engine/functions.h"
#include "global.h"
#include "enemy/bgobj.h"

// Functions in this file: bgobj_lift_init (0x0203e658), bgobj_lift_nop1 (0x0203e69c, empty state 1).

ARM void bgobj_lift_init(Entity *e) {
    e->subAction = 1;
    e->unk_2e = 2;
    if (e->parent->health == 0) {
        return;
    }
    e->parent->action = 7;
    e->parent->parent = 0;
    e->parent->zVelocity = 0x18000;
}

ARM void bgobj_lift_nop1(Entity *e) {
}
