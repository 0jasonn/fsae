#ifndef UNKNOWN_C_GAMESTATEVIEW_C_H
#define UNKNOWN_C_GAMESTATEVIEW_C_H

#include "types.h"

// Named view of data_0212c7c8 for implementer C. Same bytes as GameStateC in State_C.h, which stays unchanged.
// Field names are guesses from use; the reviewer should merge them into the shared definition (see report).
typedef struct GameSlotView {
    /* 00 */ u32 flags;
    /* 04 */ u8 unk_04;
    /* 05 */ u8 fieldBits; // bitfield written by ClearKeyUpdate
    /* 06 */ u16 counter;
} GameSlotView;

typedef struct GameStateView {
    /* 00 */ u8 playerCount;
    /* 01 */ u8 pickIndex;      // 0..3, rerolled by shuffleStage
    /* 02 */ u8 active;         // nonzero while the phase machine runs
    /* 03 */ u8 phase;
    /* 04 */ u8 phaseTimer;
    /* 05 */ u8 periodicFlag;   // 0x81 when set by isBossFloor
    /* 06 */ u8 difficulty;
    /* 07 */ u8 gameMode;       // 6 selects the alternate threshold table
    /* 08 */ u32 score;
    /* 0c */ u32 playerCounters[4];
    /* 1c */ u32 frameCount;
    /* 20 */ u32 unk_20;
    /* 24 */ u8 unk_24;
    /* 25 */ u8 unk_25;
    /* 26 */ u16 unk_26;
    /* 28 */ GameSlotView slots[4];
    /* 48 */ u8 unk_48;
    /* 49 */ u8 unk_49[5];
    /* 4e */ u8 usedPickMask;   // bit per pickIndex already used
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
    /* 70 */ u8 unk_70[0x1e];
    /* 8e */ u8 unk_8e;
    /* 8f */ u8 unk_8f;
    /* 90 */ u8 unk_90;
} GameStateView;

// 8-byte per-player flags entry (enemyTypeFlags, indexed by player). The entity type table is shared with
// CheckKenBeam/2 in state_02049020.c.
typedef struct PlayerFlags {
    /* 00 */ u32 flags;
    /* 04 */ u8 unk_04;
    /* 05 */ u8 unk_05;
    /* 06 */ u16 counter;
} PlayerFlags;
extern PlayerFlags enemyTypeFlags[];

// Same object as data_0212c7c8 in State_C.h; include only one of the two headers per file
extern GameStateView data_0212c7c8;

#endif
