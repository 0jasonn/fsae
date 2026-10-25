#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/pane.h"
#include "engine/pane_calc.h"

// pane_calc: functions Pane_calcScaledY (0x020b5a70), Pane_calcScaledX (0x020b5b30).

// Pane_calcScaledX(out, a, scale, param) (0x020b5b30, provisional name): the x counterpart of Pane_calcScaledY,
// out[index] = (base + span) * (scale - 1) - (a[0] - 1) * span and out[other] = base * (scale - 1)
extern "C" void Pane_calcScaledX(s16 *out, const s16 *a, const s16 *scale, const PaneScaleParam *param);
ARM void Pane_calcScaledX(s16 *out, const s16 *a, const s16 *scale, const PaneScaleParam *param) {
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
