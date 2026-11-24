#include "engine/functions.h"
#include "global.h"
#include "ui/widget/uiobject.h"

// Functions in this file (original names from the debug build):
//   calc_liner (0x020acab4), calc_easeIn (0x020acb04), calc_easeOut (0x020acb7c)
// They return the interpolated pair by value (ABI: the hidden result pointer is the first argument, the same as
// UIObjectCalcFunc in ui/widget/uiobject.h).

extern const s16 data_020c91fc[][2]; // easing table: the first value of each row is used by the ease curves

// Linear interpolation of from and to by ratio (0x1000 is the end)
UIPos2 calc_liner(const s32 *from, const s32 *to, s32 ratio) {
    UIPos2 result;
    s32 weight = ratio >> 3;
    s32 toX = to[0];
    s32 toY = to[1];

    result.x = (from[0] * (0x200 - weight) + toX * weight) >> 9;
    result.y = (from[1] * (0x200 - weight) + toY * weight) >> 9;
    return result;
}

// Ease-in curve: the ratio is pulled back by the table value, then interpolated as in calc_liner
UIPos2 calc_easeIn(const s32 *from, const s32 *to, s32 ratio) {
    UIPos2 result;
    s32 weight;

    weight = ratio + (((s16)data_020c91fc[(ratio << 3) >> 4][0] * (s16)-0x517) >> 12);
    weight >>= 3;
    result.x = (from[0] * (0x200 - weight) + to[0] * weight) >> 9;
    result.y = (from[1] * (0x200 - weight) + to[1] * weight) >> 9;
    return result;
}

// Ease-out curve: the same as calc_easeIn with the table value added
UIPos2 calc_easeOut(const s32 *from, const s32 *to, s32 ratio) {
    UIPos2 result;
    s32 weight;

    weight = ratio + (((s16)data_020c91fc[(ratio << 3) >> 4][0] * (s16)0x517) >> 12);
    weight >>= 3;
    result.x = (from[0] * (0x200 - weight) + to[0] * weight) >> 9;
    result.y = (from[1] * (0x200 - weight) + to[1] * weight) >> 9;
    return result;
}
