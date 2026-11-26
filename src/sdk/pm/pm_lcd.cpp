#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/gx/engine_romhalf.h"
#include "sdk/gx/gx.h"
#include "sdk/pm/pm.h"
#include "sdk/pm/pm_apply_power.h"

// PM_SetLCDPower(on) (0x0201d514): anything but 1 means off; powering the LCD off first switches the display off when it is
// on. The state is then applied through func_0201d314 (mode = on).
s32 PM_SetLCDPower(s32 on) {
    if (on != 1) {
        on = 0;
        if (Engine_ReadRomHalf() != 0) {
            GX_DispOff();
        }
    }
    return func_0201d314(on, 0, 0, 1);
}

// PM_GetLCDPower() (0x0201d550): bit 0 of the power control register at 0x04000304.
s32 PM_GetLCDPower(void) {
    if (*(volatile u16 *)0x4000304 & 1) {
        return 1;
    }
    return 0;
}
