#ifndef WIP_B_EM20_6_H
#define WIP_B_EM20_6_H

#include "engine/functions.h"
#include "enemy/em20.h"

extern const u8 em20_hitbox[]; // em20_hitbox, hitbox of em20

// Actor-specific fields of em20 (Entity offsets 0x70 onwards).
typedef struct Vars_em20 {
    u8 unk_00[0x70];
    u8 phase;         // 0x70: random start phase, set by em20_init
    u8 unk_71;
    u8 lastDirection; // 0x72: 0xff after em20_init (no direction chosen yet)
} Vars_em20;

#endif
