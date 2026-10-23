#ifndef WIP_G_SET18_H
#define WIP_G_SET18_H

#include "engine/functions.h"

// Actor fields of the Set18 family (file-local overlay, offsets from the original code).
typedef struct Vars_Set18 {
    /* 00 */ u8 unk_00[0x60];
    /* 60 */ u32 typeBits;    // ParseTypeBits(type2) when the 0x80 bit of type was set, else 0
    /* 64 */ u8 unk_64[0x14];
    /* 78 */ u16 frameTimer;  // timer * 30 frames, counted down in set18_move before the cell is cleared
    /* 7a */ u8 unk_7a[2];
    /* 7c */ u16 *cellPtr;    // BG cell under the entity, set in set18_init
} Vars_Set18;

extern const EntityFunc set18_stateTable[]; // indexed by e->action, was set18_stateTable
extern const u32 flagBits[];

#endif
