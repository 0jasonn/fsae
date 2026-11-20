#ifndef ACTOR_ENEMY_EM1D_POSSESS_H
#define ACTOR_ENEMY_EM1D_POSSESS_H

#include "engine/functions.h"
#include "engine/player.h"

// Actor em1d possession state: the enemy hangs on a player and drains hearts until the player shakes it off.
typedef struct Vars_Em1dPossess {
    /* 00 */ u8 unk_00[0x70];
    /* 70 */ u16 grabTimer;    // 0x1e when the enemy grabs the player, counts down while the player mashes keys
    /* 72 */ u16 recoverTimer; // 0x78 after each heart drain
} Vars_Em1dPossess;

extern u8 data_0212ceec[]; // playerWork[i].unk_3c, stride 0x94

extern "C" {
void func_02084a20(Entity *e); // thumb helper
}

#endif
