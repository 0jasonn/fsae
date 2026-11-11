#ifndef WIP_A_REWHALF_A_H
#define WIP_A_REWHALF_A_H

#include "engine/functions.h"
#include "engine/player.h"

typedef struct Vars_Rew {
    /* 00 */ u8 unk_00[0x78];
    /* 78 */ u16 cellA;
    /* 7a */ u8 unk_7a[2];
    /* 7c */ u16 cellB;     // 0xffff when the second cell is unused
    /* 7e */ u16 listSet;   // selects the block of cell lists
} Vars_Rew;
#define VS(e) VARS(Vars_Rew, e)

typedef struct BgmIndexEntry {
    /* 00 */ const u8 *table; // record table, byte 1 selects the cell list set
    /* 04 */ u32 unk_4;
} BgmIndexEntry;

extern const BgmIndexEntry *const bgmIndexTable[];
extern const u16 *const rewHalfListsBgm[];   // rewHalfListsBgm, indexed by a bgm row byte
extern const u16 *const rewHalfListsPick[];  // rewHalfListsPick, indexed by the pick index

void rewHalf(Entity *e);

#endif
