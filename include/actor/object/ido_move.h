#ifndef WIP_C_IDO_MOVE_H
#define WIP_C_IDO_MOVE_H

#include "engine/entity.h"

// Ido (moving floor) fields past the shared Entity header
typedef struct Vars_IdoMove {
    /* 00 */ u8 unk_00[0x60];
    /* 60 */ u32 moveCheckMask; // bit i set: player i rides the floor (low 4 bits)
    /* 64 */ u8 unk_64[0x18];
    /* 7c */ u16 prevX; // position at the start of the frame
    /* 7e */ u16 prevY;
} Vars_IdoMove;

extern "C" {
void ido_yukaMove(Entity *e); // 0x020650f4, original yukaMove(OBJ_WORK_*)
}

#endif
