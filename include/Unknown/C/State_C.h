#ifndef UNKNOWN_C_STATE_C_H
#define UNKNOWN_C_STATE_C_H

#include "Unknown/Entity.h"

// Per-player state (same layout as PlayerData in Unknown/Player.hpp)
typedef struct PlayerC {
    /* 00 */ u8 unk_00[2];
    /* 02 */ u8 unk_02;
    /* 03 */ u8 unk_03[5];
    /* 08 */ u16 unk_08;
    /* 0a */ u8 unk_0a[2];
    /* 0c */ u8 unk_0c;
    /* 0d */ u8 unk_0d[7];
    /* 14 */ u8 unk_14;
    /* 15 */ u8 unk_15[9];
    /* 1e */ u8 unk_1e;
    /* 1f */ u8 unk_1f[7];
    /* 26 */ u8 unk_26;
    /* 27 */ u8 unk_27;
    /* 28 */ Entity *unk_28;
    /* 2c */ u8 unk_2c[0xa];
    /* 36 */ u16 unk_36;
    /* 38 */ u8 unk_38;
    /* 39 */ u8 unk_39;
    /* 3a */ u8 unk_3a[2];
    /* 3c */ u8 unk_3c;
    /* 3d */ u8 unk_3d[0x57];
} PlayerC; // size 0x94

// 8-byte record of the game state block, indexed by player count
typedef struct Slot8_C {
    /* 00 */ u32 unk_00;
    /* 04 */ u8 unk_04[4];
} Slot8_C;

// Game state block (layout known up to 0x6f, see Unknown/Player.hpp for the first 0x28 bytes)
typedef struct GameStateC {
    /* 00 */ u8 unk_0; // number of players
    /* 01 */ u8 unk_1[2];
    /* 03 */ u8 unk_3;
    /* 04 */ u8 unk_4;
    /* 05 */ u8 unk_5;
    /* 06 */ u8 unk_6;
    /* 07 */ u8 unk_7[0x15];
    /* 1c */ u32 unk_1c;
    /* 20 */ u8 unk_20[6];
    /* 26 */ u16 unk_26;
    /* 28 */ Slot8_C unk_28[4];
    /* 48 */ u8 unk_48;
    /* 49 */ u8 unk_49[0x26];
    /* 6f */ u8 unk_6f;
    /* 70 */ u8 unk_70[0x20];
    /* 90 */ u8 unk_90;
} GameStateC;

extern PlayerC data_0212ceb0[4];
extern GameStateC data_0212c7c8;

#ifdef __cplusplus
extern "C" {
#endif
u32 func_020280e0(void);
u8 *func_0208da4c(void);
int func_0208de54(void);
void func_02049f38(int a);
u16 func_02048378(void);
#ifdef __cplusplus
}
#endif

// Timer-like block written by func_020482e4
typedef struct TimerC {
    /* 00 */ u8 unk_00[8];
    /* 08 */ u32 unk_08;
    /* 0c */ u32 unk_0c;
    /* 10 */ u32 unk_10;
    /* 14 */ u32 unk_14;
} TimerC;
extern TimerC data_0217d36c;

#endif
