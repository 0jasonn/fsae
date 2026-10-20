#ifndef WIP_A_HEART_LIFT_H
#define WIP_A_HEART_LIFT_H

#include "engine/functions.h"
#include "engine/player.h"

// Actor fields of the heart lift (file-local overlay).
typedef struct Vars_HeartLift {
    /* 00 */ u8 unk_00[0x72];
    /* 72 */ u16 holdTimer; // counts down while the lift waits in heart_lift_end
    /* 74 */ u8 unk_74;
    /* 75 */ u8 phase;      // 0 = placing, 1 = placed, 2 = lever moving
} Vars_HeartLift;

extern const s8 heartLiftOffsetTable[]; // heartLiftOffsetTable, dx/dy pairs indexed by animationState
extern "C" int func_02083d30(s16 x, s16 y, u16 layer);
void nemoto_leverMove(Entity *e);

#endif
