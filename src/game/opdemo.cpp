#include "engine/functions.h"
#include "engine/misc_d.h"
#include "global.h"

ARM void gufu_flash(void) {
    *(u16 *)(data_021349c0 + EFFECT_STATE_TIMER) = 0x14;
    data_021349c0[EFFECT_STATE_SCENE]++;
    data_021349c0[EFFECT_STATE_LEVEL] = 0;
    data_0212c5ac.resetValue = -1;
    PaletteFade_ClearBufferFlag();
    FadeSet(2, 8);
    SoundReq(0x1f9);
}
