#ifndef ENGINE_VBLANK_H
#define ENGINE_VBLANK_H

#include "types.h"
#include "engine/irq.h"  // HBlankDmaState hblankDma, FrameState frameState

typedef volatile u16 vu16;


#include "engine/vblank_request.h"
extern u8 data_021348f4[];
#include "engine/bg_buff.h"  // data_02158fa0 (its disp entry gives the screen base)
extern u8 data_0213cfa0[];

#endif
