#ifndef WIP_E_SHIKAKE_H
#define WIP_E_SHIKAKE_H

// Switch-block ("shikake") module (src/game/shikake.cpp). Callees and data that functions.h does not declare yet.
#include "engine/functions.h"

// One 0x18-byte shikake record (data_02134e70 is an array of them). Fields not yet understood are unk_*.
typedef struct SHIKAKEWORK_ {
    /* 00 */ u8 unk_00;
    /* 01 */ u8 unk_01;
    /* 02 */ u8 state; // 1 while the record takes part in the request check
    /* 03 */ u8 type; // kind of record: 1 = big block (shikake_bigblock), 2 = func_020227b4
    /* 04 */ u8 unk_04[2];
    /* 06 */ u16 key;
    /* 08 */ Entity *objs[4]; // objects checked by shikake_playercheck
} SHIKAKEWORK;

extern u8 data_021348e4; // number of records in data_02134bb0
extern u8 data_021348f0; // number of records in data_02134e70
extern u8 data_02134bb0[];
extern SHIKAKEWORK data_02134e70[];

void shikake_bigblock(u32 *record); // 0x02022110, too large for this unit
void func_020227b4(u32 *record); // 0x020227b4, too large for this unit

#endif
