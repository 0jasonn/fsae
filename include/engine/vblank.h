#ifndef ENGINE_VBLANK_H
#define ENGINE_VBLANK_H

#include "types.h"
#include "engine/irq.h"  // HBlankDmaState hblankDma, FrameState frameState

typedef volatile u16 vu16;


#include "engine/vblank_request.h"
extern u8 data_021348f4[];
extern u16 *data_02158fa0;      // pointer to the screen block (first word of the layer buffer data_02158fa0)
extern u8 data_0213cfa0[];

#endif
