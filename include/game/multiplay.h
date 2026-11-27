#ifndef GAME_MULTIPLAY_H
#define GAME_MULTIPLAY_H

// Declarations for the multiplay, makemap and game00 units of implementer B (0x02047454 to 0x02047e34).

#include "engine/functions.h"
#include "engine/player.h"
#include "game/ending.h"

extern "C" {
void MultiWorkInit(void);
}

// Packed 2-bit fields: the status word of comWork.recv[] (ComPacketBits)
typedef struct MultiFlagWord { u32 b0 : 2; u32 b2 : 2; u32 b4 : 2; u32 b6 : 2; } MultiFlagWord;

// Saved multiplay record (data_0212c5ec, 0x2c bytes): a copy of the per-player parts of gameState.
typedef struct MultiSaveBlock {
    /* 00 */ u32 score;             // gameState.score
    /* 04 */ u32 counters[4];       // gameState.playerCounters
    /* 14 */ u8 flag68[4];          // gameState.kakeraCount
    /* 18 */ u8 timer58[4];         // gameState.heldItems
    /* 1c */ u8 timer60[4];         // gameState.health
    /* 20 */ u8 maxHearts[4];       // gameState.maxHearts
    /* 24 */ u8 nutBits[4];         // playerWork[i].nutBits b0 | b2 << 2 | b4 << 4, one byte per player
    /* 28 */ u8 unk_50;             // copy of gameState.unk_50[0]
    /* 29 */ u8 unk_29[3];
} MultiSaveBlock;
extern MultiSaveBlock data_0212c5ec;

#include "engine/data_0212c540.h"
extern u32 data_0212c54c;
extern u32 data_0212c558;
#include "engine/cockpit_state.h"

void StopBlockInit(void);
void FadeClear(void);
void LoadTokiWave(void);
void Enemy_ArmSharedState(void);
void BgmSet(void);
#include "engine/com_work.h"
void GetSetWorkSp(u8 a, u8 b, u8 c);
extern u16 data_0212c510;
extern u16 data_0212c514;
extern u16 data_0212c520;
extern u8 data_0212c4b8;
extern "C" {
void CalcHeartLevel(void);
}

extern u8 data_0216efa8;                    // makemap state byte
#include "engine/frame_counter.h"
#include "engine/key_ring.h"
extern u32 data_0212c550;
extern u32 data_0212c554;

// Task tables indexed by a state byte (rodata)
extern void (*const multiplayMakemapTable[])(void);   // multiplayMakemapTable
extern void (*const game00TaskTable[])(void);         // game00TaskTable


void FloorInit(void);  // C++ linkage (original_names.tsv)

void AutoSet(void); // C++ linkage, original AutoSet(); 0x02023940 (game/autoset.h has its tables)

#endif
