#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "ui/widget/pane.h"
#include "ui/widget/pane_calc.h"

// Combines the rectangle coordinates with the window frame inset.
void Pane_calcRectSum(s16 *outA, s16 *outB, const s16 *origin, const s16 *size, const s16 *inset) {
    int adjustedY;
    int adjustedX;

    adjustedY = origin[1] + size[1] - inset[3];
    adjustedX = origin[0] + inset[0];
    outA[0] = adjustedX;
    outA[1] = adjustedY;
    outB[0] = size[0] - inset[0];
    outB[1] = inset[3];
}

// Pane_calcScaledX(out, a, scale, param) (0x020b5b30, provisional name): the x counterpart of Pane_calcScaledY,
// out[index] = (base + span) * (scale - 1) - (a[0] - 1) * span and out[other] = base * (scale - 1)
extern "C" void Pane_calcScaledX(s16 *out, const s16 *a, const s16 *scale, const PaneScaleParam *param);
void Pane_calcScaledX(s16 *out, const s16 *a, const s16 *scale, const PaneScaleParam *param) {
    u8 flag;
    int index;
    int other;
    int sum;

    flag = param->index;
    index = flag ? 1 : 0;
    other = (index + 1) % 2;
    sum = param->base[index] + param->span[index];
    out[index] = sum * (scale[index] - 1) - (a[0] - 1) * param->span[index];
    out[other] = param->base[other] * (scale[other] - 1);
}
