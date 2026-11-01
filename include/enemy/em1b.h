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

#endif
