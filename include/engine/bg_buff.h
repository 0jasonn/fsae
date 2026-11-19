#ifndef ENGINE_BG_BUFF_H
#define ENGINE_BG_BUFF_H

#include "types.h"
#include "engine/display_state.h"

// Background layer buffer (original BG_BUFF_, 0xb004 bytes). There are two, back to back: data_02158fa0 (its display
// entry is displayState.bg[2]) and data_02163fa4 (displayState.bg[1]); GetBgBuffAdrs picks one by layer and
// DemoBgBuffClear clears both. The map is 64x64 cells, a cell index is x | y << 6.
// dsd also has symbols inside both buffers (data_02158fa4/data_02163fa8 screen, data_0215afa4/data_02165fa8 attr,
// data_0215bfa4/data_02166fa8 screenSave, data_0215dfa4/data_02168fa8 cellMap, data_0215efa4 cellIndex).
typedef struct BG_BUFF_ {
    /* 0000 */ DispBg *disp;            // display entry of the layer (set by BgInit); MultiRoomInit writes the scroll
    /* 0004 */ u16 screen[0x1000];      // screen block filled by BlockCopy (FrameSet/PartsSet); openDoor clears entries
    /* 2004 */ u8 attr[0x1000];         // per-cell attribute (terrain/occupancy: 0 free, 0x18 door, 0x1d pushed block)
    /* 3004 */ u16 screenSave[0x1000];  // copy of screen taken by MultiRoomSet before MakeMapScreen
    /* 5004 */ u16 cellMap[0x800];      // per-cell index (MultiRoomInit fills it with 0xffff before MapLoad)
    /* 6004 */ u16 cellIndex[0x800];    // reverse of cellMap, built by MultiRoomInit
    /* 7004 */ u8 unk_7004[0xb004 - 0x7004];
} BG_BUFF_;

extern BG_BUFF_ data_02158fa0; // 0x02158fa0
extern BG_BUFF_ data_02163fa4; // 0x02163fa4

#endif
