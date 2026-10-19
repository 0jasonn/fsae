#ifndef UNKNOWN_WIP_F_PLATE_H
#define UNKNOWN_WIP_F_PLATE_H

#include "object/setcommon.h"

// Plate actor fields (file-local overlay for src/object/plate.cpp and rupee.cpp, not shared).
typedef struct Vars_Plate {
    /* 00 */ u8 unk_00[0x60];
    /* 60 */ u32 limit;   // target value, compared against count in plate_move
    /* 64 */ u32 count;   // value shown by the rupee children (rupee_move reads it from the parent)
} Vars_Plate;
#define VPLATE(e) VARS(Vars_Plate, e)

extern u8 data_0212c4dc;     // game flag, 1 while counting up, 2 when the count is snapped to limit
extern u8 data_021349c0[];   // game state, byte 0x27 nonzero when the actor should be removed

void plate_posY_set(Entity *e);
void rupee_move(Entity *e, s8 dx, u32 divisor);

#endif
