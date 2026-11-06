#include "engine/functions.h"
#include "global.h"
#include "engine/misc.h"
#include "actor/object/objdecls_f.h"

// Zelda fade module, 0x0205b700 ZeldaFadeFinish (original name; follows ZeldaFadeFlagGet in zeldafade.cpp)

extern u8 data_02171d1c; // 1 while no fade partner is active (see ZeldaFadeFlagGet)

void ZeldaFadeFinish(void) {
    StopEffectWindow();
    data_02171d1c = 1;
    *((u8 *)&blendRequest + 4) = 1; // fade running flag
    blendRequest.blendEnabled = 0;
}
