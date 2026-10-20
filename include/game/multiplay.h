#ifndef WIP_B_MULTIPLAY_H
#define WIP_B_MULTIPLAY_H

// Declarations for the multiplay, makemap and game00 units of implementer B (0x02047454 to 0x02047e34).

#include "engine/functions.h"
#include "engine/player.h"
#include "enemy/ending.h"

extern "C" {
void MultiWorkInit(void);
}

// Packed 2-bit fields: the player flag byte at 0x8b and the first word of the 0x34-byte records at data_0212ca44
typedef struct MultiFlagByte { u8 b0 : 2; u8 b2 : 2; u8 b4 : 2; u8 b6 : 2; } MultiFlagByte;
typedef struct MultiFlagWord { u32 b0 : 2; u32 b2 : 2; u32 b4 : 2; u32 b6 : 2; } MultiFlagWord;

// Game state block at data_0212c7c8 (only the offsets used by the multiplay code are named)
#define GS_U8(off) (*((u8 *)&data_0212c7c8 + (off)))
#define GS_U16(off) (*(u16 *)((u8 *)&data_0212c7c8 + (off)))
#define GS_U32(off) (*(u32 *)((u8 *)&data_0212c7c8 + (off)))

// Saved multiplay record at data_0212c5ec (byte and word arrays indexed by player)
extern u8 data_0212c5ec[];
#define MS_U8(off) (*((u8 *)data_0212c5ec + (off)))
#define MS_U32(off) (*(u32 *)((u8 *)data_0212c5ec + (off)))

extern u16 data_0212c540;
extern u32 data_0212c54c;
extern u32 data_0212c558;
extern u8 data_021361a0[];

void RandomSetInit(void);
void StopBlockInit(void);
void PlWorkReset(void);
void FadeClear(void);
void Knife_Single_SinglePlay_Initialize(void);
void func_0202a5f4(void);
void ShikakeInit(void);
void LoadTokiWave(void);
void Enemy_ArmSharedState(void);
void BgmSet(void);
void PlayerTrans(void);
extern u32 data_0212c538;
extern u8 data_02134cb0[];
extern u8 data_0212c9a8[];
void GetSetWorkSp(u8 a, u8 b, u8 c);
extern u8 data_0212c9ec[];
extern u16 data_0212c594;
extern "C" {
void InitCircleWindow(u16 a, u16 b);
void MakeTriangleWindow(s16 a, s16 b, s16 c, s16 d);
}
void LoadJyouchuu(void);
void func_0204363c(void);
extern u16 data_0212c510;
extern u16 data_0212c514;
extern u16 data_0212c520;
extern u16 data_0212c58c[];
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
void BgInit(void);
void CheckInit(void);
}
extern "C" {
void CalcHeartLevel(void);
}

// Byte at offset off of player slot i (PlayerData is 0x94 bytes; fields past 0x3d are not named in player.h)
#define PLAYER_BYTE(i, off) (((u8 *)&data_0212ceb0[i])[off])

extern u8 localPlayerIndex;
extern u8 data_0216efa8;                    // makemap state byte
extern u8 frameCounter[];                  // game state byte block, byte 0x12 cleared by multiplay_init
extern u8 data_0212ca44[];                  // 0x34-byte records, first word read by multiplay_init
extern PlayerData *data_0212c53c;           // current player slot pointer
extern u32 data_0212c550;
extern u32 data_0212c554;

// Task tables indexed by a state byte (rodata)
extern void (*const multiplayMakemapTable[])(void);   // multiplayMakemapTable
extern void (*const game00TaskTable[])(void);         // game00TaskTable

#endif
