#ifndef WIP_B_EM23_3_H
#define WIP_B_EM23_3_H

#include "engine/functions.h"

extern const u8 data_020d2d98[]; // hitbox of em23

// Actor-specific fields of em23 (Offsets are those of Entity).
typedef struct Vars_em23 {
    u8 unk_00[0x6c];
    u16 respawnDelay; // 0x6c: set to 600 by em23_init when it is nonzero
} Vars_em23;

#endif
