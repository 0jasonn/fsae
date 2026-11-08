#ifndef KNIFE_COMM_SINGLEPLAY_A_H
#define KNIFE_COMM_SINGLEPLAY_A_H

#include "engine/functions.h"
#include "engine/player.h"
#include "knife/comm/single_play.h"
#include "knife/comm/single_play_api.h"
#include "knife/comm/singleplay_work_api.h"
#include "knife/comm/singleplay_2.h"
#include "engine/misc.h"

extern u8 data_0211b298[]; // rodata block of tuning values; see singleplay_2.h

// SinglePlay functions defined or called by the files of implementer A (plain names, `this` as void *).
extern "C" {
void Knife_Single_SinglePlay_Update(void *self, PlayerData *player0, PlayerData *player1, u16 keysDown, u16 keysHeld);
BOOL Knife_Single_SinglePlay_CheckCommand(void *self, PlayerData *player0, PlayerData *player1);
void Knife_Single_SinglePlay_UpdateCommand(void *self, PlayerData *player0, PlayerData *player1);
void Knife_Single_SinglePlay_UpdateMovePartner(void *self, SpWorkPair *pair);
BOOL Knife_Single_SinglePlay_UpdateEnemyCheck(void *self, SpWorkPair *pair);
BOOL Knife_Single_SinglePlay_UpdateWallCheck(void *self, SpWorkPair *pair);
}



// C++ functions (original names) called by the update code
int Em30CheckAttack(Entity *e);
u8 Em30GetRightColor(Entity *e);
s32 abs_s32(s32 value);

// Thumb map-cell helpers (C++ symbols from the debug build): cell kind / class at an offset of the entity
int func_02083ccc(Entity *e, s16 x, s16 y);
int func_02083d18(Entity *e, int dx, int dy);
int func_02083c74(Entity *e, int dx, int dy);

// Rodata read by UpdateWallCheck: s16 offset tables (x, y pairs per facing) and two three-byte tables
typedef struct SpByte3 {
    u8 v[3];
} SpByte3;
extern const SpByte3 data_020dda98;
extern const SpByte3 data_020dda9c;
extern const s16 data_020ddaa0[];
extern const s16 data_020ddac4[];
extern const s16 data_020ddad4[];
extern const s16 data_020ddae4[];

// Rodata read by UpdateEnemyCheck: four key masks (indexed by facing), two s16 offset tables and the Em30 hit window block.
typedef struct SpKeyMasks {
    u16 v[4];
} SpKeyMasks;
extern const SpKeyMasks data_020ddb38;
extern const s16 data_0211b2dc[];   // s16 x offset per facing
extern const s16 data_0211b2f4[];   // (x, y) s16 offset pairs per facing
extern EntityNode data_0212c6d0;   // end sentinel of the object list (the head itself is data_0212c6b0[4])

#endif
