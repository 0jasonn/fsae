#ifndef ENGINE_OBJAFFINE_H
#define ENGINE_OBJAFFINE_H

#include "types.h"

// Sine and cosine pairs (s16, 12 fractional bits) indexed by angle >> 4, rodata at 0x020c91fc
extern const s16 data_020c91fc[];

extern "C" {
void func_02012ad0(s32 *mtx, s32 sin, s32 cos);                           // thumb, 0x02012ad0: rotation matrix 2x2
void MTX_ScaleApply22(s32 *dst, const s32 *src, s32 scaleX, s32 scaleY); // 0x02012adc
}

#endif
