#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/pane.h"
#include "engine/pane_calc.h"

// pane_calc: functions Pane_calcScaledY (0x020b5a70), Pane_calcScaledX (0x020b5b30).

// Pane_calcScaledY(out, a, scale, param) (0x020b5a70, provisional name): out[index] = base * (scale - 1) for the entry
// index (0 or 1) of param, out[other] = (base + span) * (scale - 1) - (a[1] - 1) * span for the other entry
extern "C" void Pane_calcScaledY(s16 *out, const s16 *a, const s16 *scale, const PaneScaleParam *param);
ARM void Pane_calcScaledY(s16 *out, const s16 *a, const s16 *scale, const PaneScaleParam *param) {
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
