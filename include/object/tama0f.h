#ifndef WIP_C_TAMA0F_H
#define WIP_C_TAMA0F_H

// Actor-specific overlays for the tama0f family (src/wip/C/tama0f*.cpp).
#include "engine/functions.h"
#include "global.h"
#include "engine/player.h"

typedef struct Vars_Tama0f {
    /* 00 */ u8 unk_00[0x70];
    /* 70 */ s32 fireTimer; // frames left for the fire shot
    /* 74 */ s32 unk_74; // written by tama0f_init only
} Vars_Tama0f;

// Overlay of a parent actor: its state byte at 0x79
typedef struct Vars_TamaParent {
    /* 00 */ u8 unk_00[0x6e];
    /* 6e */ u16 itemIndex; // cycles 0..2 to pick the item list in tama0f_init and tama0f_break
    /* 70 */ u8 unk_70[9];
    /* 79 */ u8 parentState;
} Vars_TamaParent;

#endif
