#ifndef WIP_K_FXMUL_H
#define WIP_K_FXMUL_H

#include "types.h"

// Rounded 20.12 fixed point multiply (FX_Mul of the NitroSDK): (v1 * v2 + 0.5) in 1/0x1000 steps.
static inline s32 FX_Mul(s32 v1, s32 v2) {
    return (s32)((((s64)v1 * v2) + 0x800LL) >> 12);
}

#endif
