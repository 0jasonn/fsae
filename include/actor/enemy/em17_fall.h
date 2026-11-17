#ifndef ACTOR_ENEMY_EM17_FALL_H
#define ACTOR_ENEMY_EM17_FALL_H

#include "engine/functions.h"

// Overlay of the em17 fields em17_fall touches (offsets are those of Entity).
typedef struct Vars_Em17Fall {
    /* 00 */ u8 unk_00[0x70];
    /* 70 */ u16 shakeTimer; // countdown of the shaking state
} Vars_Em17Fall;

// Falling step of em17 (original em17_fall(OBJ_WORK_*)), 0x0203da28.
void em17_fall(Entity *e);

#endif
