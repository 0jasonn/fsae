#include "engine/functions.h"
#include "global.h"

// Functions in this file (original names from the debug build):
//   calc_liner (0x020acab4), calc_easeIn (0x020acb04), calc_easeOut (0x020acb7c)
// They return the interpolated pair by value (ABI: the hidden result pointer is the first argument, the same as
// UIObjectCalcFunc in game/uiobject.h). Shared header: the prototypes there should return CalcPos2 (see the report).

extern const s16 data_020c91fc[][2]; // easing table: the first value of each row is used by the ease curves

typedef struct CalcPos2 {
    s32 x;
    s32 y;
} CalcPos2;

// Linear interpolation of from and to by ratio (0x1000 is the end)
extern "C" CalcPos2 calc_liner(const s32 *from, const s32 *to, s32 ratio);
ARM CalcPos2 calc_liner(const s32 *from, const s32 *to, s32 ratio) {
    CalcPos2 result;
    s32 weight = ratio >> 3;
    s32 toX = to[0];
    s32 toY = to[1];

    result.x = (from[0] * (0x200 - weight) + toX * weight) >> 9;
    result.y = (from[1] * (0x200 - weight) + toY * weight) >> 9;
    return result;
}

// Ease-in curve: the ratio is pulled back by the table value, then interpolated as in calc_liner
extern "C" CalcPos2 calc_easeIn(const s32 *from, const s32 *to, s32 ratio);
ARM CalcPos2 calc_easeIn(const s32 *from, const s32 *to, s32 ratio) {
    CalcPos2 result;
    s32 weight;

    weight = ratio + (((s16)data_020c91fc[(ratio << 3) >> 4][0] * (s16)-0x517) >> 12);
    weight >>= 3;
    result.x = (from[0] * (0x200 - weight) + to[0] * weight) >> 9;
    result.y = (from[1] * (0x200 - weight) + to[1] * weight) >> 9;
    return result;
}

// Ease-out curve: the same as calc_easeIn with the table value added
extern "C" CalcPos2 calc_easeOut(const s32 *from, const s32 *to, s32 ratio);
ARM CalcPos2 calc_easeOut(const s32 *from, const s32 *to, s32 ratio) {
    CalcPos2 result;
    s32 weight;

    weight = ratio + (((s16)data_020c91fc[(ratio << 3) >> 4][0] * (s16)0x517) >> 12);
    weight >>= 3;
    result.x = (from[0] * (0x200 - weight) + to[0] * weight) >> 9;
    result.y = (from[1] * (0x200 - weight) + to[1] * weight) >> 9;
    return result;
}
