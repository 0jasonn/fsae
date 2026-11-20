#ifndef ACTOR_ENEMY_EM23_5_H
#define ACTOR_ENEMY_EM23_5_H

#include "engine/functions.h"

#include "engine/frame_counter.h"

// Actor-specific fields of em23 used by the aim code.
typedef struct Vars_em23_aim {
    u8 unk_00[0x64];
    Entity *aimTarget; // 0x64: the player the actor is aiming at (FindTargetInRange result when set)
} Vars_em23_aim;

#endif
