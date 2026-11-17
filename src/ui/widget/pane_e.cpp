#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "ui/widget/pane.h"
#include "ui/widget/pane_e_api.h"
#include "ui/widget/pane_calc.h"

// pane_e.cpp: functions Pane_calcRectPair (0x020b5950) and Pane_tailCallCalc (0x020b5984), both matching.

extern "C" void Pane_calcScaledBase(void *a, void *b, void *c);

// Pane_calcRectPair(outA, outB, a, b, c) (0x020b5950, provisional name): outA = a, outB = {b.x - c.y, c.z}
void Pane_calcRectPair(s16 *outA, s16 *outB, const s16 *a, const s16 *b, const s16 *c) {
    outA[0] = a[0];
    outA[1] = a[1];
    outB[0] = b[0] - c[1];
    outB[1] = c[2];
}

// Pane_tailCallCalc(self, unused, b, c) (0x020b5984, provisional name): forwards to Pane_calcScaledBase without the second argument
void Pane_tailCallCalc(void *self, void *unused, void *b, void *c) {
    Pane_calcScaledBase(self, b, c);
}

// Provisional name. Compute the frame's right-hand rectangle.
void Pane_calcRightRect(s16 *outA, s16 *outB, const s16 *origin, const s16 *size, const s16 *inset) {
    int originY;

    originY = origin[1];
    outA[0] = origin[0] + size[0] - inset[1];
    outA[1] = originY;
    outB[0] = inset[1];
    outB[1] = size[1] - inset[3];
}

// Provisional name. Preserve the four-argument callback ABI while scaling both base coordinates.
void Pane_calcScaledBaseWithContext(s16 *out, void *unused, const s16 *scale, const PaneScaleParam *param) {
    u8 flag;
    int index;
    int other;

    flag = param->index;
    index = flag ? 1 : 0;
    other = (index + 1) % 2;
    out[index] = param->base[index] * (scale[index] - 1);
    out[other] = param->base[other] * (scale[other] - 1);
}
