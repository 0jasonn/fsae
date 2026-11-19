#ifndef ENGINE_HUD_TILE_OBJ_H
#define ENGINE_HUD_TILE_OBJ_H

#include "types.h"

// One HUD tile object: an OAM-style attribute word and a tile word (set up by CockpitInit).
typedef struct HudTileEntry {
    /* 00 */ u32 sizeLo : 8;
    u32 setting : 2;     // bits 8-9: cockpit_obj_set writes the same value to both entries
    u32 unk_00b : 6;
    u32 sizeHi : 9;
    u32 unk_00c : 5;
    u32 mode : 2;
    /* 04 */ union {
        u16 tileWord;    // make_item_color rewrites the palette bank (bits 12..15) of the whole word
        struct {
            u16 tile : 10;
            u16 unk_04b : 2;
            u16 palette : 4;
        };
    };
    /* 06 */ u16 unk_06;
} HudTileEntry;

// HUD tile object block (data_0212c4a0, 0x18 bytes; data_0212c4b8 follows).
typedef struct HudTileObj {
    /* 00 */ u32 unk_00;
    /* 04 */ s32 frame;               // advanced modulo 0x30 by cockpit_obj_trans, read by rupee_disp
    /* 08 */ HudTileEntry entries[2]; // CockpitInit clears both (data_0212c4a8) before setting them up
} HudTileObj;
extern HudTileObj data_0212c4a0;

#endif
