#ifndef WIP_D_PL_H
#define WIP_D_PL_H

#include "engine/entity.h"
#include "engine/player.h"

// File-local view of one PlayerData entry (data_0212ceb0[n], 0x94 bytes) with the fields the player functions use
typedef struct PlWork {
    /* 00 */ u8 unk_00;
    /* 01 */ u8 unk_01;
    /* 02 */ u8 unk_02;
    /* 03 */ u8 unk_03;
    /* 04 */ u8 unk_04;
    /* 05 */ u8 state; // 3 or 4 while the player is in a special state
    /* 06 */ u8 unk_06;
    /* 07 */ u8 unk_07; // bit 7 is a flag, see BindPlayer
    /* 08 */ u16 unk_08;
    /* 0a */ u8 unk_0a; // low nibble only
    /* 0b */ u8 unk_0b;
    /* 0c */ u8 unk_0c;
    /* 0d */ u8 unk_0d;
    /* 0e */ u8 unk_0e;
    /* 0f */ u8 unk_0f;
    /* 10 */ u8 unk_10;
    /* 11 */ u8 unk_11;
    /* 12 */ u8 unk_12;
    /* 13 */ u8 unk_13;
    /* 14 */ u8 unk_14;
    /* 15 */ u8 unk_15[5];
    /* 1a */ u8 unk_1a;
    /* 1b */ u8 unk_1b;
    /* 1c */ u8 unk_1c[2];
    /* 1e */ u8 unk_1e;
    /* 1f */ u8 unk_1f;
    /* 20 */ u8 unk_20;
    /* 21 */ u8 unk_21;
    /* 22 */ u16 unk_22;
    /* 24 */ u16 unk_24;
    /* 26 */ u8 unk_26;
    /* 27 */ u8 unk_27;
    /* 28 */ Entity *entity;
    /* 2c */ Entity *weapon;
    /* 30 */ u8 unk_30;
    /* 31 */ u8 unk_31[3];
    /* 34 */ u8 unk_34;
    /* 35 */ u8 unk_35;
    /* 36 */ u16 unk_36;
    /* 38 */ u8 unk_38;
    /* 39 */ u8 unk_39;
    /* 3a */ u8 unk_3a;
    /* 3b */ u8 unk_3b;
    /* 3c */ u8 unk_3c;
    /* 3d */ u8 unk_3d;
    /* 3e */ u8 unk_3e;
    /* 3f */ s8 yOffset;
    /* 40 */ u8 unk_40[0x4a];
    /* 8a */ u8 unk_8a;
    /* 8b */ u8 unk_8b; // bits 2..3 hold a color/palette index, see PlWorkColorReset
    /* 8c */ u8 unk_8c[8];
} PlWork; // size 0x94

#endif
