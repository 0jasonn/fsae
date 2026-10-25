#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/pane.h"
#include "engine/pane_calc.h"

// pane_scale: functions PaneScale_get (0x020b76bc) and Pane_calcScaledBase (0x020b76d0), both matching. The table
// data_02126c4c holds PaneScaleParam records of five bytes each.

extern u8 data_02126c4c[];

// PaneScale_get(index) (0x020b76bc, provisional name): the record index of the table data_02126c4c
extern "C" PaneScaleParam *PaneScale_get(u32 index);
ARM PaneScaleParam *PaneScale_get(u32 index) {
    return (PaneScaleParam *)(data_02126c4c + index * 5);
}

// Pane_calcScaledBase(out, scale, param) (0x020b76d0, provisional name): out[index] = base[index] * (scale[index] - 1)
// for the entry index of param, and the same for the other entry
extern "C" void Pane_calcScaledBase(s16 *out, const s16 *scale, const PaneScaleParam *param);
ARM void Pane_calcScaledBase(s16 *out, const s16 *scale, const PaneScaleParam *param) {
    u8 flag;
    int index;
    int other;

    flag = param->index;
    index = flag ? 1 : 0;
    other = index ^ 1;
    out[index] = param->base[index] * (scale[index] - 1);
    out[other] = param->base[other] * (scale[other] - 1);
}
