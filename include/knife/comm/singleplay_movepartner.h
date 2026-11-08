#ifndef KNIFE_COMM_SINGLEPLAY_MOVEPARTNER_H
#define KNIFE_COMM_SINGLEPLAY_MOVEPARTNER_H

#include "engine/functions.h"
#include "engine/player.h"
#include "knife/comm/single_play.h"
#include "knife/comm/single_play_api.h"
#include "knife/comm/singleplay_work_api.h"
#include "knife/comm/singleplay_2.h"
#include "engine/misc.h"

extern const u8 data_0211b298[]; // const here: the scheduler hoists the table load above the stores to PlayerData

// SinglePlay functions the partner update defines or calls (plain names, `this` as void *).
extern "C" {
void Knife_Single_SinglePlay_UpdateMovePartner(void *self, SpWorkPair *pair);
BOOL Knife_Single_SinglePlay_UpdateEnemyCheck(void *self, SpWorkPair *pair);
BOOL Knife_Single_SinglePlay_UpdateWallCheck(void *self, SpWorkPair *pair);
BOOL Knife_Single_SinglePlay_UpdateFormationMode(void *self, SpWorkPair *pair);
BOOL Knife_Single_SinglePlay_UpdateWarpZoneCheck(void *self, SpWorkPair *pair);
BOOL Knife_Single_SinglePlay_returnZero_020956ec(void *self, SpWorkPair *pair);
BOOL Knife_Single_SinglePlay_returnZero_02096e40(void *self, SpWorkPair *pair);
void Knife_Single_SinglePlay_UpdateNear(void *self, SpWorkPair *pair);
void Knife_Single_SinglePlay_UpdateFar(void *self, SpWorkPair *pair);
void Knife_Single_SinglePlay_SinglePlayWork_SetTargetPos(void *pair);
int Knife_Single_SinglePlay_SinglePlayLogList_SetLog_09a2e0(Knife::Single::SinglePlay::SinglePlayLogList *self, const Entity *obj, u16 kind, s32 c, s16 threshold, s16 sumAddA, s16 sumAddB);
int func_020898b4(int cell);
int func_02083ce4(s16 x, s16 y, u16 layer);
int func_02083d30(s16 x, s16 y, u16 layer);
}

// Bit view of PlayerData::unk_3e: the top two bits are cleared by the partner update.
typedef struct PlayerBits3e {
    u8 lo : 6;
    u8 hi : 2;
} PlayerBits3e;

// abs_s32 is a C++ function (symbols.txt: _Z7abs_s32l)
s32 abs_s32(s32 value);

extern const s16 data_02178de0;   // step threshold of the partner logic (s16 in bss)

#endif
