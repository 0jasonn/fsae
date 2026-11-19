#ifndef ENGINE_FLOOR_PARTS_STATE_H
#define ENGINE_FLOOR_PARTS_STATE_H

#include "types.h"

// Floor parts / iroyuka state block (data_0216f820, 0xc bytes; data_0216f82c follows).
typedef struct FloorPartsState {
    /* 00 */ u8 flags;         // cleared by parts_init; frame_select tests bit 0x10
    /* 01 */ u8 unk_01;        // cleared by FloorInit
    /* 02 */ u16 partId;       // part id of the part being set (parts_set)
    /* 04 */ u32 iroyukaIndex; // pending player index + 1 (ChangeIroyuka); UpdateIroyuka handles and clears it
    /* 08 */ u32 iroyukaCount; // number of iroyuka cell entries (data_0216f934), counted up by FloorInit
} FloorPartsState;
extern FloorPartsState data_0216f820;

#endif
