#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/pane.h"

// pane_e.cpp: functions Pane_calcRectPair (0x020b5950) and Pane_tailCallCalc (0x020b5984), both matching.

extern "C" void func_020b76d0(void *a, void *b, void *c);

// Pane_calcRectPair(outA, outB, a, b, c) (0x020b5950, provisional name): outA = a, outB = {b.x - c.y, c.z}
extern "C" void Pane_calcRectPair(s16 *outA, s16 *outB, const s16 *a, const s16 *b, const s16 *c);
ARM void Pane_calcRectPair(s16 *outA, s16 *outB, const s16 *a, const s16 *b, const s16 *c) {
    outA[0] = a[0];
    outA[1] = a[1];
    outB[0] = b[0] - c[1];
    outB[1] = c[2];
}

// Pane_tailCallCalc(self, unused, b, c) (0x020b5984, provisional name): forwards to func_020b76d0 without the second argument
extern "C" void Pane_tailCallCalc(void *self, void *unused, void *b, void *c);
ARM void Pane_tailCallCalc(void *self, void *unused, void *b, void *c) {
    func_020b76d0(self, b, c);
}
