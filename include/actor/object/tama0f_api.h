#ifndef WIP_A_TAMA0F_A_H
#define WIP_A_TAMA0F_A_H

#include "engine/functions.h"
#include "engine/player.h"

// Overlay of the storm actor (tama0f_storm)
typedef struct Vars_Tama0fStorm {
    /* 00 */ u8 unk_00[0x70];
    /* 70 */ s32 stormTimer;   // frames the storm keeps chasing the player, 0 = homing on the parent
    /* 74 */ u32 lifeCounter;  // counts up, wraps after 0x21c
} Vars_Tama0fStorm;
#define VS(e) VARS(Vars_Tama0fStorm, e)

// Overlay of the parent actor
typedef struct Vars_Tama0fParent {
    /* 00 */ u8 unk_00[0x71];
    /* 71 */ u8 stormActive;
} Vars_Tama0fParent;

extern u8 data_0212ced8[]; // playerWork[0].entity, stride 0x94
#define PLAYER_ENTITY(i) (*(Entity **)(data_0212ced8 + (i) * 0x94))

extern "C" BOOL func_02085a88(Entity *a, Entity *b, s32 w, s32 h); // thumb, overlap test
void tama0f_storm(Entity *e);

#endif
