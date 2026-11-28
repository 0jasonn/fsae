#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/pm/pm.h"

// PMi_LCDOnAvoidReset() (0x0201d70c): makes sure the LCD power is on before a forced power off, switching it on (with
// the bottom backlight off first) and retrying until the PM driver accepts each step. The PXI wait flags are restored.
void PMi_LCDOnAvoidReset(void) {
    u32 savedFlags;

    OS_SpinWaitSysCycles(0x360000);
    savedFlags = data_020dfbe4;
    data_020dfbe4 = 0xe;
    if (PM_GetLCDPower() != 1) {
        if (PM_SetBackLight(2, 0) != 0) {
            do {
                OS_SpinWaitSysCycles(0x51d23);
            } while (PM_SetBackLight(2, 0) != 0);
        }
        if (PM_SetLCDPower(1) == 0) {
            do {
                OS_SpinWaitSysCycles(5);
            } while (PM_SetLCDPower(1) == 0);
        }
    }
    data_020dfbe4 = savedFlags;
}
