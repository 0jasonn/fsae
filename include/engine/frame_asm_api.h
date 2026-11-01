#ifndef ENGINE_FRAME_ASM_API_H
#define ENGINE_FRAME_ASM_API_H

// Functions defined in src/engine/frame_asm*.cpp.

#include "engine/entity.h"

extern "C" {
u32 Bits_CountLeadingZeros(u32 value);
void Frame_AddSp0xa4PopR4R11(void);
void Frame_PopR3ToR7Return(void);
u32 Swp_Exchange(u32 value, u32 *target);
}

#endif
