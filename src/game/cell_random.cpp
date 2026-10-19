#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "game/cellcommon.h"

// Functions in this file (original names from the debug build):
//   random_baneyuka_set

// Cell table of the baneyuka random set
extern const u16 data_020d7d92[];

// Places the baneyuka tile at the cell of key, in layer 0 or 0x20 (picked at random)
ARM void random_baneyuka_set(u16 key, u16 index) {
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

// Table of pointers (bgmIndexTable) indexed by the game state; each entry is a record table of 8-byte rows
extern u32 bgmIndexTable[];
extern u8 data_0212c7c8[];

// Places the ochiba tile at the cell of key, chosen at random (the 0x8000 variant is used for key 0xcb)
ARM void random_ochiba_set(u16 key, u16 index) {
    u8 state;
    u8 *row;
    u16 tile;

    state = data_0212c7c8[1];
    if (state != 3) {
        if (state < 5) {
            return;
        }
        row = *(u8 **)((u8 *)bgmIndexTable[state] + data_0212c7c8[0x48] * 8);
        if (row[1] != 2 && row[1] != 0xc) {
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
ARM void random_rupeemizu_set(u16 key, u16 index) {
    u8 state;
    u8 *row;
    u16 tile;

    state = data_0212c7c8[1];
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
    row = *(u8 **)((u8 *)bgmIndexTable[state] + data_0212c7c8[0x48] * 8);
    if (row[1] != 2 && row[1] != 1 && row[1] != 8 && row[1] != 9 && row[1] != 0xc) {
        if (row[1] != 0xb) {
            return;
        }
    }
    if (key == 0x82) {
        tile = (Random() & 0xff) < 0x7f ? 0x81 : 0x80;
        func_02083694(tile, index, 0x4000);
    }
}
