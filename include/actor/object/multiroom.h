#ifndef WIP_C_MULTIROOM_H
#define WIP_C_MULTIROOM_H

#include "engine/functions.h"
#include "engine/entity.h"

#include "engine/map_state.h"
#include "engine/bg_buff.h" // layer buffers data_02158fa0, data_02163fa4

#include "game/triangle.h"          // triangleTable, cleared by MultiRoomInit
extern u32 *const data_020d7110[];       // per-room map data
extern u16 *const data_020d714c[];       // per-room background animation, may be null

void BgAnmInit(u16 *a);                  // 0x02023cc0
void MultiRoomInit(u16 room);            // 0x02056f4c

// bg2StSet has C++ linkage (original bg2StSet()), 0x02057494.
void bg2StSet(void);

#endif
