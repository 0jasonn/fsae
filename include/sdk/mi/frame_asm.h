#ifndef SDK_MI_FRAME_ASM_H
#define SDK_MI_FRAME_ASM_H

#include "engine/entity.h"

extern "C" {
void Frame_PopR3ToR7Return(void);
u32 Swp_Exchange(u32 value, u32 *target);
}

#endif
