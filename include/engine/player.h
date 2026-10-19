#ifndef UNKNOWN_PLAYER_H
#define UNKNOWN_PLAYER_H

#include "engine/entity.h"

// Per-player state, one per connected Link
typedef struct PL_WORK_ { // original name PL_WORK_
    /* 00 */ u8 unk_00[2];
    /* 02 */ u8 unk_02;
    /* 03 */ u8 unk_03[5];
    /* 08 */ u16 unk_08;
    /* 0a */ u8 unk_0a[2];
    /* 0c */ u8 state;
    /* 0d */ u8 unk_0d[7];
    /* 14 */ u8 unk_14;
    /* 15 */ u8 unk_15[9];
    /* 1e */ u8 unk_1e;
    /* 1f */ u8 unk_1f[7];
    /* 26 */ u8 unk_26;
    /* 27 */ u8 unk_27;
    /* 28 */ Entity *entity;
    /* 2c */ u8 unk_2c[0xa];
    /* 36 */ u16 statusFlags;
    /* 38 */ u8 stateTimer;
    /* 39 */ u8 unk_39;
    /* 3a */ u8 unk_3a[2];
    /* 3c */ u8 unk_3c;
    /* 3d */ u8 unk_3d[0x57];
} PlayerData; // size 0x94

extern PlayerData data_0212ceb0[4];
typedef struct UnkStruct_0212c7c8 {
    /* 00 */ u8 unk_0; // number of players
    /* 01 */ u8 unk_1[2];
    /* 03 */ u8 difficulty;
    /* 04 */ u8 unk_4;
    /* 05 */ u8 unk_5;
    /* 06 */ u8 stage;
    /* 07 */ u8 unk_7[0x1f];
    /* 26 */ u16 unk_26;
} UnkStruct_0212c7c8;
extern UnkStruct_0212c7c8 data_0212c7c8;
extern u16 data_0212c584[4];

#endif
