#ifndef GAME_BGINIT_H
#define GAME_BGINIT_H

#include "engine/functions.h"

// Background scroll/animation initialisation (original BgInit()), 0x02021a10.
void BgInit(void);

// Layer buffers data_02158fa0 / data_02163fa4; BgInit points them at displayState.bg[2] / bg[1].
#include "engine/bg_buff.h"
extern u32 data_02134a68[]; // background animation slots, 8 x 8 bytes (first word cleared)

#endif
