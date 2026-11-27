#ifndef ACTOR_ENEMY_EM20_MAGNE_H
#define ACTOR_ENEMY_EM20_MAGNE_H

#include "engine/entity.h"

// Actor fields used by magneCheck (0x0203ef24, the magnet-pull check of the em20/kamen enemies)
typedef struct Vars_MagneCheck {
    /* 00 */ u8 unk_00[0x71];
    /* 71 */ u8 pullTimer; // frames the enemy has been pulled in the same direction
    /* 72 */ u8 pullDir;   // current pull direction (0xff = none)
} Vars_MagneCheck;
#define VMAGNE(e) VARS(Vars_MagneCheck, e)

extern const s8 magneShakeOffsets[]; // 0x020d2a80, sideways shake offsets (4 entries) while being pulled

#endif
