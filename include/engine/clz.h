#ifndef WIP_K_CLZ_H
#define WIP_K_CLZ_H

#include "types.h"

// Count of leading zero bits (the ARM clz instruction); the operand register is reused for the result.
static inline u32 CountLeadingZeros(u32 value) {
    asm { clz value, value }
    return value;
}

#endif
