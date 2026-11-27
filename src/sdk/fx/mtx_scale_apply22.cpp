#include "global.h"
#include "types.h"

#include "sdk/fx/fx.h"

// dst = src scaled by (scaleX, scaleY) for a 2x2 fixed-point (20.12) matrix: the first row by X, the second by Y.
void MTX_ScaleApply22(const s32 *src, s32 *dst, s32 scaleX, s32 scaleY) {
    dst[0] = (s32)(((s64)scaleX * src[0]) >> 12);
    dst[1] = (s32)(((s64)scaleX * src[1]) >> 12);
    dst[2] = (s32)(((s64)scaleY * src[2]) >> 12);
    dst[3] = (s32)(((s64)scaleY * src[3]) >> 12);
}
