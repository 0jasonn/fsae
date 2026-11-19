#ifndef WIP_C_MULTIROOM_H
#define WIP_C_MULTIROOM_H

#include "engine/functions.h"
#include "engine/entity.h"

#include "engine/map_state.h"

extern u8 triangleTable[];               // 0x021387a0, cleared by MultiRoomInit (size 0x800)
extern u16 data_0215dfa4[];              // 0x0215dfa4, cell index lists of the two layers
extern u16 data_02168fa8[];
extern u32 *const data_020d7110[];       // per-room map data
extern u16 *const data_020d714c[];       // per-room background animation, may be null
extern u8 data_02158fa0[];               // 0x02158fa0, layer buffers (first word: pointer to the screen block)
extern u8 data_02163fa4[];

void BgAnmInit(u16 *a);                  // 0x02023cc0
void MultiRoomInit(u16 room);            // 0x02056f4c

// bg2StSet has C++ linkage (original bg2StSet()), 0x02057494.
void bg2StSet(void);

#endif
