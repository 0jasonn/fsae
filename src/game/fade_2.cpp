#include "engine/functions.h"
#include "enemy/ending.h"
#include "global.h"

// Implementer B, round 6: FadeMain (0x020462c4), fade_in (0x020462f4), fade_out (0x0204636c).

ARM void FadeMain(void) {
    if (data_0212c5ac.blendEnabled == 0) {
        return;
    }
    fadeModeTable[data_0212c5ac.blendMode](&data_0212c5ac);
}

ARM void fade_in(FADE_WORK_ *w) {
    if (w->fadeRunning != 0) {
        w->blendWeight = w->blendWeight - w->blendStep;
        if (w->blendWeight <= 0) {
            w->blendWeight = 0;
            w->blendEnabled = 0;
        }
        MakeFadeBuff256(w->blendWeight);
    } else {
        w->blendWeight = w->blendWeight - w->blendStep;
        data_0212c75c.unk_6a = w->blendWeight >> 4;
        if (w->blendWeight <= 0) {
            w->blendEnabled = 0;
            data_0212c75c.unk_6a = 0;
        }
    }
}

ARM void fade_out(FADE_WORK_ *w) {
    if (w->fadeRunning != 0) {
        w->blendWeight = w->blendWeight - w->blendStep;
        if (w->blendWeight <= 0) {
            w->blendWeight = 0;
            w->blendEnabled = 0;
        }
        MakeFadeBuff256(0x100 - w->blendWeight);
    } else {
        w->blendWeight = w->blendWeight - w->blendStep;
        data_0212c75c.unk_6a = 0x10 - (w->blendWeight >> 4);
        if (w->blendWeight <= 0) {
            w->blendEnabled = 0;
            data_0212c75c.unk_6a = 0x10;
        }
    }
}
