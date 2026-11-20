#ifndef SDK_MI_DMA_CONFLICT_API_H
#define SDK_MI_DMA_CONFLICT_API_H

// Functions defined in src/engine/dma_conflict*.cpp.

#include "engine/entity.h"

extern "C" {
void Dma_CheckConflict(s32 skip, u32 mode);
}

#endif
