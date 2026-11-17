#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "ui/widget/pane.h"
#include "ui/widget/pane_calc.h"

// Adjusts two coordinate pairs for the window frame.
void Pane_calcRectOffset(s16 *outA, s16 *outB, const s16 *origin, const s16 *size, const s16 *inset) {
    int shiftedY;

    shiftedY = origin[1] + inset[2];
    outA[0] = origin[0];
    outA[1] = shiftedY;
    outB[0] = inset[0];
    outB[1] = size[1] - inset[2];
}

// Pane_calcScaledY(out, a, scale, param) (0x020b5a70, provisional name): out[index] = base * (scale - 1) for the entry
// index (0 or 1) of param, out[other] = (base + span) * (scale - 1) - (a[1] - 1) * span for the other entry
extern "C" void Pane_calcScaledY(s16 *out, const s16 *a, const s16 *scale, const PaneScaleParam *param);
void Pane_calcScaledY(s16 *out, const s16 *a, const s16 *scale, const PaneScaleParam *param) {
    u8 flag;
    int index;
    int other;
    int sum;

    flag = param->index;
    index = flag ? 1 : 0;
    other = (index + 1) % 2;
    out[index] = param->base[index] * (scale[index] - 1);
    sum = param->base[other] + param->span[other];
    out[other] = sum * (scale[other] - 1) - (a[1] - 1) * param->span[other];
}
