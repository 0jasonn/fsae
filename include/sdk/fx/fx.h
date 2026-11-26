#ifndef SDK_FX_FX_H
#define SDK_FX_FX_H

// TwlSDK FX library: fixed point vectors and matrices (20.12 format) and the square root unit.
#include "types.h"

typedef struct VecFx32 {
    s32 x;
    s32 y;
    s32 z;
} VecFx32;

typedef struct MtxFx22 {
    s32 _00;
    s32 _01;
    s32 _10;
    s32 _11;
} MtxFx22;

extern "C" {
s32 FX_Sqrt(s32 value);
s32 FX_GetSqrtResult(void);
void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
void MTX_Identity22_(MtxFx22 *mtx);

// Not decompiled yet.
s32 VEC_Distance(const VecFx32 *a, const VecFx32 *b);
}

#endif
