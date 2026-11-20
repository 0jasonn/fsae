#ifndef ENGINE_PLAYER_H
#define ENGINE_PLAYER_H

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
    /* 0a */ u8 unk_0a; // only the low nibble is used
    /* 0b */ u8 unk_0b; // bit 7 is cleared by set38
    /* 0c */ u8 state;
    /* 0d */ u8 unk_0d;
    /* 0e */ u8 unk_0e;
    /* 0f */ u8 unk_0f; // low two bits are tested by set14
    /* 10 */ u8 unk_10;
    /* 11 */ u8 unk_11;
    /* 12 */ u8 unk_12;
    /* 13 */ u8 unk_13;
    /* 14 */ u8 unk_14; // countdown timer (AfterPlayer decrements it)
    /* 15 */ u8 unk_15;
    /* 16 */ u8 unk_16;
    /* 17 */ u8 unk_17;
    /* 18 */ u8 unk_18;
    /* 19 */ u8 unk_19;
    /* 1a */ u8 unk_1a;
    /* 1b */ u8 actionFlags; // bits 0x01, 0x08, 0x20, 0x40 and 0xc0 are tested by the sword and tame code
    /* 1c */ u8 heldItem; // id of the item the player holds (cockpit_move copies it to cockpitState.item / item2p)
    /* 1d */ u8 unk_1d;
    /* 1e */ u8 hitFlags; // bits 0x80 and 0x20 are tested by em2a, 0x60 by hit_jelly; also the equipment (boots) flags:
                          // boots stay while nonzero, 0x40 without 0x80 selects the active boots state (boots_init, boots_2)
    /* 1f */ u8 unk_1f;
    /* 20 */ u8 unk_20;
    /* 21 */ u8 tameState; // nonzero while tame is active; >= 0x14 selects the second tame table
    /* 22 */ u16 unk_22;
    /* 24 */ u16 unk_24;
    /* 26 */ u8 unk_26;
    /* 27 */ u8 unk_27;
    /* 28 */ Entity *entity;
    /* 2c */ Entity *weapon;
    /* 30 */ u8 unk_30; // countdown timer (AfterPlayer decrements it); multiplay_main sets 0x2d on a bind
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
    /* 3e */ union {
        u8 unk_3e;
        struct {
            u8 b0 : 2; // power: sword level (sword_move damage, radar power, kinomi)
            u8 b2 : 2; // defense (em2a_4 damage, radar defense, kinomi, katti kind)
            u8 b4 : 2; // speed (radar speed, kinomi)
            u8 b6 : 2; // speed shift of the partner (singleplay_movepartner, singleplay_waitpartner)
        } nutBits; // two-bit counters cleared by ClearNut
    };
    /* 3f */ s8 yOffset;
    /* 40 */ u8 unk_40[0x4a];
    /* 8a */ u8 unk_8a; // countdown timer (AfterPlayer decrements it)
    /* 8b */ struct {
        u8 pairRole : 2; // set to 1 / 3 for the two players of the single-player pair (and swapped with it); pot_puton tests 0
        u8 color : 2;    // color/palette index (PlWorkColorReset, iroyuka, crystal); cell kind 0x176 + color is the player's own
        u8 bind : 3;     // bind state (multiplay_main, BindPlayer); shifted left by the single-player update, tested by set11
        u8 partner : 1;  // marks the partner of the single-player mode (multiplay_main, frontcheck)
    } paletteBits;
    /* 8c */ u8 unk_8c[4];
    /* 90 */ Entity *holdObject; // object the player is attached to (the boat in set53_row)
} PlayerData; // size 0x94

extern PlayerData playerWork[4];
extern PlayerData *data_0212c53c; // current (local) player slot, set by multiplay_init
// One 8-byte record per player inside the game state (enemyTypeFlags points at the first one)
typedef struct GameSlot {
    /* 00 */ u32 flags;
    /* 04 */ union {
        u32 word4; // second save word, stored whole by setKnifeSaveData4S
        struct {
            u8 unk_04;
            u8 fieldBits; // bitfield written by ClearKeyUpdate
            u16 counter;
        };
    };
} GameSlot;

// One word of GameState.slotWords (per save slot)
typedef union GameSlotWord {
    u32 word;
    u8 stageProgress; // stage progress byte (setKnifeSaveData4S, ClearNewStageUpdate): bits 0-1 the next stage level in
                      // mode 5, bits 4-6 the stages cleared in mode 6; doorsel_init reads bits 0-1 and 2-3
} GameSlotWord;

// Game state block (gameState, 0xa0 bytes: MultiWorkInit clears it whole). Other symbols point inside it:
// data_0212c7d4 (+0x0c), enemyTypeFlags (+0x28), keyTypeFlags (+0x2d), data_0212c7f6 (+0x2e), data_0212c810 (+0x48),
// data_0212c81c (+0x54), data_0212c820 (+0x58), data_0212c824 (+0x5c), data_0212c828 (+0x60), data_0212c82c (+0x64),
// data_0212c830 (+0x68), data_0212c838 (+0x70), data_0212c84c (+0x84), data_0212c858 (+0x90).
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
    /* 50 */ u8 unk_50[4];
    /* 54 */ u8 itemLevel[4];      // per player (data_0212c81c): set by itemlevel, row of the set01/setspawn/takara tables
    /* 58 */ u8 heldItems[4];      // per player (data_0212c820): held item id, copied to PlayerData.heldItem by makemap_00
    /* 5c */ u8 keys[4];           // per player (data_0212c824): AddKey adds one, usekey takes one
    /* 60 */ u8 health[4];         // per player (data_0212c828): health in eighths of a heart (AddHeart, MPlayerSet)
    /* 64 */ u8 maxHearts[4];      // per player (data_0212c82c): heart containers (utsuwa); AddHeart caps health at 8 each
    /* 68 */ u8 kakeraCount[4];    // per player (data_0212c830): kakera count (kakera_full, item_4, radar)
    /* 6c */ u8 unk_6c;
    /* 6d */ u8 unk_6d;
    /* 6e */ u8 unk_6e;
    /* 6f */ u8 unk_6f;
    /* 70 */ Entity *radarChild[4]; // per type2 (data_0212c838): the rader child while it is shown, else NULL
    /* 80 */ s16 targetX; // target position of the heart marker (light_marker)
    /* 82 */ s16 targetY;
    /* 84 */ u8 startCells[8];     // (x, y) start cell per player (data_0212c84c), copied by MPlayerSet
    /* 8c */ u8 unk_8c;
    /* 8d */ u8 unk_8d;
    /* 8e */ u8 unk_8e;       // game state byte
    /* 8f */ u8 unk_8f;
    /* 90 */ GameSlotWord slotWords[4]; // one word per save slot (data_0212c858); MultiWorkInit keeps it across clears
} GameState;
extern GameState gameState;
extern u16 playerKeysPrev[4];

#endif
