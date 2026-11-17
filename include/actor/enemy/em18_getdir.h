#ifndef ACTOR_ENEMY_EM18_GETDIR_H
#define ACTOR_ENEMY_EM18_GETDIR_H

#include "engine/functions.h"

// Turn of the actor: getdir alternates a 0x70 flag (wide or narrow turn).
typedef struct Vars_Em18Turn {
    /* 00 */ u8 unk_00[0x70];
    /* 70 */ u8 turnFlag;
} Vars_Em18Turn;

extern const s8 getdir_offsetTable[]; // direction offsets, indexed by a random 0..15 (turnFlag set) or 0..3

// Picks a new direction from the facing towards the parent plus a random offset (original getdir(OBJ_WORK_*)), 0x0203dfd0.
void getdir(Entity *e);

#endif
