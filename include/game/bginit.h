#ifndef GAME_BGINIT_H
#define GAME_BGINIT_H

#include "engine/functions.h"

// Background scroll/animation initialisation (original BgInit()), 0x02021a10.
void BgInit(void);

// Layer buffers: the first word of each holds a pointer to the scroll position (data_0212c77c / data_0212c770).
extern u8 data_02158fa0[];
extern u8 data_02163fa4[];
extern u16 data_0212c770;
extern u16 data_0212c77c;
extern u32 data_02134a68[]; // background animation slots, 8 x 8 bytes (first word cleared)

#endif
