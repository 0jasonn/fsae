#ifndef WIP_B_MULTIPLAY_H
#define WIP_B_MULTIPLAY_H

// Declarations for the multiplay, makemap and game00 units of implementer B (0x02047454 to 0x02047e34).

#include "engine/functions.h"
#include "engine/player.h"
#include "actor/enemy/ending.h"

extern "C" {
void MultiWorkInit(void);
}

// Packed 2-bit fields: the player flag byte at 0x8b and the status word of comWork.recv[] (ComPacketBits)
typedef struct MultiFlagByte { u8 b0 : 2; u8 b2 : 2; u8 b4 : 2; u8 b6 : 2; } MultiFlagByte;
typedef struct MultiFlagWord { u32 b0 : 2; u32 b2 : 2; u32 b4 : 2; u32 b6 : 2; } MultiFlagWord;

// Saved multiplay record (data_0212c5ec, 0x2c bytes): a copy of the per-player parts of gameState.
typedef struct MultiSaveBlock {
    /* 00 */ u32 score;             // gameState.score
    /* 04 */ u32 counters[4];       // gameState.playerCounters
    /* 14 */ u8 flag68[4];          // gameState.playerFlag68 (kakera count)
    /* 18 */ u8 timer58[4];         // gameState.playerTimer58
    /* 1c */ u8 timer60[4];         // gameState.playerTimer60 (health)
    /* 20 */ u8 maxHearts[4];       // gameState.maxHearts
    /* 24 */ MultiFlagByte nutBits; // packed 2-bit nut counters
    /* 25 */ u8 unk_25[3];
    /* 28 */ u32 unk_50;            // copy of gameState.unk_50
} MultiSaveBlock;
extern MultiSaveBlock data_0212c5ec;

#include "engine/data_0212c540.h"
extern u32 data_0212c54c;
extern u32 data_0212c558;
#include "engine/cockpit_state.h"

void RandomSetInit(void);
void StopBlockInit(void);
void PlWorkReset(void);
void FadeClear(void);
void Knife_Single_SinglePlay_Initialize(void);
void ClearWorkBuffer(void);
void ShikakeInit(void);
void LoadTokiWave(void);
void Enemy_ArmSharedState(void);
void BgmSet(void);
void PlayerTrans(void);
extern u32 data_0212c538;
extern u8 data_02134cb0[];
#include "engine/com_work.h"
void GetSetWorkSp(u8 a, u8 b, u8 c);
void InitCircleWindow(u16 a, u16 b); // C++ linkage, original InitCircleWindow(unsigned short, unsigned short)
extern "C" {
void MakeTriangleWindow(s16 a, s16 b, s16 c, s16 d);
}
void LoadJyouchuu(void);
void func_0204363c(void);
extern u16 data_0212c510;
extern u16 data_0212c514;
extern u16 data_0212c520;
extern u16 playerKeys[];
extern u8 data_0212c4b8;
extern "C" {
void FloorInit(void);
void AutoSet(void);
void CockpitInit(void);
void CheckPlsSet(void);
void StopEffectWindow(void);
void Cockpit(void);
}
extern u8 data_0212caf0[];
extern "C" {
void CheckInit(void);
}
extern "C" {
void CalcHeartLevel(void);
}

extern u8 localPlayerIndex;
extern u8 data_0216efa8;                    // makemap state byte
#include "engine/frame_counter.h"
extern u32 data_0212c550;
extern u32 data_0212c554;

// Task tables indexed by a state byte (rodata)
extern void (*const multiplayMakemapTable[])(void);   // multiplayMakemapTable
extern void (*const game00TaskTable[])(void);         // game00TaskTable

// BgInit has C++ linkage (original BgInit()), so it is declared outside the extern "C" blocks.
void BgInit(void);

#endif
