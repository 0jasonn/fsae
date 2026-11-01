#ifndef UNKNOWN_PLAYER_H
#define UNKNOWN_PLAYER_H

#include "engine/entity.h"

// Per-player state, one per connected Link
typedef struct PL_WORK_ { // original name PL_WORK_
    /* 00 */ u8 unk_00;
    /* 01 */ u8 unk_01;
    /* 02 */ u8 unk_02;
    /* 03 */ u8 unk_03;
    /* 04 */ u8 inUse; // nonzero while the slot holds a player
    /* 05 */ u8 specialState; // 3 or 4 while the player is in a special state, 0 otherwise
    /* 06 */ u8 unk_06;
    /* 07 */ u8 unk_07; // bit 7 is a flag, see BindPlayer
    /* 08 */ u16 motionId; // animation/motion code set per Link action (walk 4, stand-up 0xc, item get 0xad, dead 0x1af)
    /* 0a */ u8 unk_0a;
    /* 0b */ u8 unk_0b; // bit 7 is cleared by set38
    /* 0c */ u8 state;
    /* 0d */ u8 unk_0d;
    /* 0e */ u8 unk_0e;
    /* 0f */ u8 unk_0f; // low two bits are tested by set14
    /* 10 */ u8 unk_10;
    /* 11 */ u8 unk_11;
    /* 12 */ u8 unk_12;
    /* 13 */ u8 unk_13;
    /* 14 */ u8 unk_14;
    /* 15 */ u8 unk_15;
    /* 16 */ u8 unk_16;
    /* 17 */ u8 unk_17;
    /* 18 */ u8 unk_18;
    /* 19 */ u8 unk_19;
    /* 1a */ u8 unk_1a;
    /* 1b */ u8 actionFlags; // bits 0x01, 0x08, 0x20, 0x40 and 0xc0 are tested by the sword and tame code
    /* 1c */ u8 unk_1c;
    /* 1d */ u8 unk_1d;
    /* 1e */ u8 hitFlags; // bits 0x80 and 0x20 are tested by em2a, 0x60 by hit_jelly
    /* 1f */ u8 unk_1f;
    /* 20 */ u8 unk_20;
    /* 21 */ u8 tameState; // nonzero while tame is active; >= 0x14 selects the second tame table
    /* 22 */ u16 unk_22;
    /* 24 */ u16 unk_24;
    /* 26 */ u8 unk_26;
    /* 27 */ u8 unk_27;
    /* 28 */ Entity *entity;
    /* 2c */ Entity *weapon;
    /* 30 */ u8 unk_30;
    /* 31 */ u8 unk_31;
    /* 32 */ u8 unk_32;
    /* 33 */ u8 unk_33;
    /* 34 */ u8 unk_34;
    /* 35 */ u8 unk_35;
    /* 36 */ u16 statusFlags;
    /* 38 */ u8 stateTimer;
    /* 39 */ u8 unk_39;
    /* 3a */ u8 unk_3a;
    /* 3b */ u8 unk_3b;
    /* 3c */ u8 callState; // nonzero blocks the cockpit call animation
    /* 3d */ u8 unk_3d;
    /* 3e */ u8 unk_3e;
    /* 3f */ s8 yOffset;
    /* 40 */ u8 unk_40[0x4a];
    /* 8a */ u8 unk_8a;
    /* 8b */ u8 paletteBits; // bits 2..3 hold a color/palette index (PlWorkColorReset); bits 4..6 are tested by set11
    /* 8c */ u8 unk_8c[8];
} PlayerData; // size 0x94

extern PlayerData data_0212ceb0[4];
// One 8-byte record per player inside the game state (enemyTypeFlags points at the first one)
typedef struct GameSlot {
    /* 00 */ u32 flags;
    /* 04 */ u8 unk_04;
    /* 05 */ u8 fieldBits; // bitfield written by ClearKeyUpdate
    /* 06 */ u16 counter;
} GameSlot;

// Game state block (data_0212c7c8). Other symbols point inside it: data_0212c7d4 (+0x0c), enemyTypeFlags (+0x28),
// keyTypeFlags (+0x2d), data_0212c7f6 (+0x2e), data_0212c810 (+0x48).
typedef struct GameState {
    /* 00 */ u8 playerCount;
    /* 01 */ u8 unk_01;       // 0..3 rerolled by shuffleStage; also compared with 2 and 5 (mode) and indexes youseiFrameTable
    /* 02 */ u8 active;       // nonzero while the phase machine runs
    /* 03 */ u8 difficulty;   // indexes em2f_healthByDifficulty; get_maplevel uses difficulty + 3 in mode 2 (guess)
    /* 04 */ u8 phaseTimer;
    /* 05 */ u8 periodicFlag; // 0x81 when set by isBossFloor
    /* 06 */ u8 level;        // 1..3: indexes the per-level health and speed tables; heart level and rank use it
    /* 07 */ u8 gameMode;     // 6 selects the alternate threshold table
    /* 08 */ u32 score;
    /* 0c */ u32 playerCounters[4];
    /* 1c */ u32 frameCount;
    /* 20 */ u32 unk_20;
    /* 24 */ u8 unk_24;
    /* 25 */ u8 unk_25;
    /* 26 */ u16 unk_26;
    /* 28 */ GameSlot slots[4];
    /* 48 */ u8 unk_48;
    /* 49 */ u8 unk_49[5];
    /* 4e */ u8 usedPickMask; // bit per unk_01 value already used
    /* 4f */ u8 phaseFlags;
    /* 50 */ u8 unk_50[8];
    /* 58 */ u8 playerTimer58[4];
    /* 5c */ u8 unk_5c[4];
    /* 60 */ u8 playerTimer60[4];
    /* 64 */ u8 unk_64[4];
    /* 68 */ u8 playerFlag68[4];
    /* 6c */ u8 unk_6c;
    /* 6d */ u8 unk_6d;
    /* 6e */ u8 unk_6e;
    /* 6f */ u8 unk_6f;
    /* 70 */ u8 unk_70[0x1c];
    /* 8c */ u8 unk_8c;
    /* 8d */ u8 unk_8d;
    /* 8e */ u8 unk_8e;       // game state byte
    /* 8f */ u8 unk_8f;
} GameState;
extern GameState data_0212c7c8;
extern u16 data_0212c584[4];

#endif
