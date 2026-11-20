#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "game/cellcommon.h"
#include "engine/player.h"
#include "game/frame_load.h"

// Functions in this file (original names from the debug build):
//   random_baneyuka_set

// Cell table of the baneyuka random set
extern const u16 data_020d7d92[];

// Places the baneyuka tile at the cell of key, in layer 0 or 0x20 (picked at random)
void random_baneyuka_set(u16 key, u16 index) {
    s32 cell;

    cell = SearchCellTbl(data_020d7d92, key);
    if (cell == 0xffff) {
        return;
    }
    if ((Random() & 1) == 0) {
        cell = 0x20;
    }
    func_02083694((u16)cell, index, 0x4000);
}

// Places the ochiba tile at the cell of key, chosen at random (the 0x8000 variant is used for key 0xcb)
void random_ochiba_set(u16 key, u16 index) {
    u8 state;
    FRAME_INFO_ *frame;
    u16 tile;

    state = gameState.unk_01;
    if (state != 3) {
        if (state < 5) {
            return;
        }
        frame = bgmIndexTable[state][gameState.unk_48].frame;
        if (frame->roomNo != 2 && frame->roomNo != 0xc) {
            return;
        }
    }
    if ((u16)(key + 0x43 + 0xff00) <= 1) {
        tile = (Random() & 0xff) < 0x7f ? 0xbb : 0xb1;
        func_02083694(tile, index, 0x4000);
        return;
    }
    if (key != 0xcb && key != 0xbe) {
        return;
    }
    tile = (Random() & 0xff) < 0x7f ? 0xc9 : 0xbf;
    func_02083694(tile, index, 0x8000);
}

// Places the rupeemizu tile at the cell of key 0x82, chosen at random between two tiles
void random_rupeemizu_set(u16 key, u16 index) {
    u8 state;
    FRAME_INFO_ *frame;
    u16 tile;

    state = gameState.unk_01;
    if (state == 3 || state == 0) {
        if (key == 0x82) {
            tile = (Random() & 0xff) < 0x7f ? 0x81 : 0x80;
            func_02083694(tile, index, 0x4000);
        }
        return;
    }
    if (state < 5) {
        return;
    }
    frame = bgmIndexTable[state][gameState.unk_48].frame;
    if (frame->roomNo != 2 && frame->roomNo != 1 && frame->roomNo != 8 && frame->roomNo != 9 && frame->roomNo != 0xc) {
        if (frame->roomNo != 0xb) {
            return;
        }
    }
    if (key == 0x82) {
        tile = (Random() & 0xff) < 0x7f ? 0x81 : 0x80;
        func_02083694(tile, index, 0x4000);
    }
}
