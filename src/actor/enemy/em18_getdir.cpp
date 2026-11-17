#include "engine/functions.h"
#include "global.h"
#include "actor/enemy/em18_getdir.h"

// Functions in this file: getdir (0x0203dfd0).

// Both branches are written out: the compiler merges their identical tails.
void getdir(Entity *e) {
    u8 facing;

    if (VARS(Vars_Em18Turn, e)->turnFlag != 0) {
        facing = GetFacingDirection(e, e->parent);
        e->direction = (facing + getdir_offsetTable[Random() & 0xf]) & 0x1f;
    } else {
        facing = GetFacingDirection(e, e->parent);
        e->direction = (facing + getdir_offsetTable[Random() & 0x3]) & 0x1f;
    }
    VARS(Vars_Em18Turn, e)->turnFlag ^= 1;
}
