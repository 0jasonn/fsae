#include "engine/functions.h"
#include "global.h"
#include "actor/enemy/em0f_2.h"

#define VEm0f(e) VARS(Vars_Em0f, e)

// Every 8 frames the dash speed changes by accel; accel shrinks by 7 each time, and when the speed drops to 0 the dash
// is counted off (both health branches are identical in the ROM).
void spdchange(Entity *e) {
    if ((VEm0f(e)->homingTimer & 7) != 0) {
        return;
    }
    e->speed += (s16)VEm0f(e)->accel;
    if (e->health > 0x28) {
        if ((s16)VEm0f(e)->accel >= -0x100) {
            VEm0f(e)->accel -= 7;
        }
        if (e->speed <= 0) {
            e->speed = 0;
            VEm0f(e)->accel = 0x3f;
            VEm0f(e)->dashCount--;
            if (VEm0f(e)->dashCount == 0) {
                homingMoveSet(e);
            }
        }
    } else {
        if ((s16)VEm0f(e)->accel >= -0x100) {
            VEm0f(e)->accel -= 7;
        }
        if (e->speed <= 0) {
            e->speed = 0;
            VEm0f(e)->accel = 0x3f;
            VEm0f(e)->dashCount--;
            if (VEm0f(e)->dashCount == 0) {
                homingMoveSet(e);
            }
        }
    }
}
