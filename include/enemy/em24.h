#ifndef UNKNOWN_B_ACTOR_0204001C_H
#define UNKNOWN_B_ACTOR_0204001C_H

#include "engine/entity.h"

typedef struct Vars_0204001c {
    /* 00 */ u8 unk_00[0x64];
    /* 64 */ Entity *aimTarget; // aim object, allocated by func_02084f98 (0x58 bytes)
    /* 68 */ u8 unk_68[0x14];
    /* 7c */ u16 aimX;
    /* 7e */ u16 aimY;
} Vars_0204001c;
#define V(e) VARS(Vars_0204001c, e)

extern const void *em24_swordHitboxes[];
extern const s8 em24_smokeOffsets[];
extern const s8 em24_arrowOffsets[];
extern const EntityFunc em25_stateTable[];
extern const EntityFunc em24_stateTable[];



#endif
