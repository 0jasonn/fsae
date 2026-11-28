#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/pm/pm.h"
#include "sdk/pxi/pxi_fifo.h"

// PMi_SetAmp(enabled) (0x0201cee0): sends the amplifier on/off command (0x10); does nothing while the LCD is off.
s32 PMi_SetAmp(u32 enabled) {
    if (PM_GetLCDPower() == 0) {
        return 0;
    }
    return PM_SendUtilityCommand(0x10, (u16)enabled, NULL);
}

// PM_GetBackLight(top, bottom) (0x0201cf10): reads the backlight state; *top and *bottom (when not NULL) receive 1 if
// that screen's backlight is on.
s32 PM_GetBackLight(u32 *top, u32 *bottom) {
    u16 state;
    s32 error = PM_SendUtilityCommand(0xf, 3, &state);

    if (error != 0) {
        return error;
    }
    if (top != NULL) {
        *top = (state & 8) ? 1 : 0;
    }
    if (bottom != NULL) {
        *bottom = (state & 4) ? 1 : 0;
    }
    return error;
}

// PMi_SendPxiData(word) (0x0201cf70): sends one word to the ARM7 PM service on PXI tag 8, retrying until accepted.
void PMi_SendPxiData(u32 word) {
    while (PXI_SendWordByFifo(8, word, 0) != 0) {
    }
}
