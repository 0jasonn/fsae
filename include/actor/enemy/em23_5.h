#ifndef WIP_B_EM23_5_H
#define WIP_B_EM23_5_H

#include "engine/functions.h"

extern u16 frameCounter; // frame counter (frameCounter)

// Actor-specific fields of em23 used by the aim code.
typedef struct Vars_em23_aim {
    u8 unk_00[0x64];
    Entity *aimTarget; // 0x64: the player the actor is aiming at (func_02084f98 result when set)
} Vars_em23_aim;

#endif
