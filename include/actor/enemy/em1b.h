#ifndef ENEMY_EM1B_H
#define ENEMY_EM1B_H

#include "engine/entity.h"

// Type 1 (trailing segments). trail[] holds one packed (dx, dy) byte per frame slot, each nibble offset by 8.
typedef struct Vars_Em1bType1 {
    /* 00 */ u8 unk_00[0x70];
    /* 70 */ u16 savedX;
    /* 72 */ u16 savedY;
    /* 74 */ u8 trail[8];
    /* 7c */ u32 frameAnims; // one animation nibble per trail slot
} Vars_Em1bType1;

typedef struct Vars_Em1b {
    /* 00 */ u8 unk_00[0x70];
    /* 70 */ u16 savedX;     // copied from x in em1b_type0, one per frame
    /* 72 */ u16 savedY;     // copied from y in em1b_type0
    /* 74 */ Entity *child1; // second part, set by em1b_type0_init
    /* 78 */ Entity *child2; // third part
    /* 7c */ u8 unk_7c;
    /* 7d */ s8 dirDelta;    // added to e->direction every 4 frames, picked from em1b_dirDeltaTable
} Vars_Em1b;

#endif
