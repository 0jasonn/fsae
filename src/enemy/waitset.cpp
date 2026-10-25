#include "engine/functions.h"
#include "global.h"
#include "enemy/waitset.h"

// Functions in this file: waitset (0x0203e764).

// The u16 at 0x70 is the wait counter; its meaning depends on the caller's Vars, so it is named here only.
typedef struct Vars_waitset {
    u8 unk_00[0x70];
    u16 waitTimer; // frames to wait, set to 0x3c
} Vars_waitset;

ARM void waitset(Entity *e) {
    e->action = 1;
    VARS(Vars_waitset, e)->waitTimer = 0x3c;
    e->spriteSettings.b0 = 0;
}
