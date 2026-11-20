#include "engine/functions.h"
#include "engine/wip_a_decls.h"
#include "global.h"
#include "types.h"
#include "engine/pm_power_api.h"

// Applies PM sound, LED and amplifier state (0x0201d314).
// Partial state view: timestamps at +0x0c/+0x10, saved amplifier setting at +0x18.
extern "C" s32 func_0201d314(s32 mode, u32 value, s32 force, s32 useSound) {
    u32 cycles = 0x51d23;
    u32 zero = 0;

    if (mode != 0) {
        if (mode != 1) {
            goto return_true;
        }
        if (force == 0 && *(u32 *)0x02fffc3c - ((u32 *)&data_0212b920)[3] <= 7) {
            return 0;
        }

        if (value != 0) {
            if (useSound != 0) {
                if (PMi_SetSoundVolume(value) != 0) {
                    do {
                        OS_SpinWaitSysCycles(cycles);
                    } while (PMi_SetSoundVolume(value) != 0);
                }
            } else if (PMi_SetLEDAsync(value, 0, 0) != 0) {
                do {
                    OS_SpinWaitSysCycles(cycles);
                } while (PMi_SetLEDAsync(value, (PMiCallback)zero, zero) != 0);
            }
        }

        *(volatile u16 *)0x04000304 = *(volatile u16 *)0x04000304 | 1;
        if (PMi_SetAmp(*((u32 *)&data_0212b920 + 6)) != 0) {
            do {
                OS_SpinWaitSysCycles(cycles);
            } while (PMi_SetAmp(*((u32 *)&data_0212b920 + 6)) != 0);
        }
        goto return_true;
    }

    if (PMi_SetAmp(0) != 0) {
        do {
            OS_SpinWaitSysCycles(cycles);
        } while (PMi_SetAmp(0) != 0);
    }

    if (*(u32 *)0x02fffc3c - ((u32 *)&data_0212b920)[4] <= 2) {
        PMi_WaitVBlank();
        PMi_WaitVBlank();
    }
    *(volatile u16 *)0x04000304 = *(volatile u16 *)0x04000304 & 0xfffe;
    ((u32 *)&data_0212b920)[3] = *(u32 *)0x02fffc3c;

    if (value != 0) {
        if (useSound != 0) {
            if (PMi_SetSoundVolume(value) != 0) {
                do {
                    OS_SpinWaitSysCycles(cycles);
                } while (PMi_SetSoundVolume(value) != 0);
            }
        } else if (PMi_SetLEDAsync(value, 0, 0) != 0) {
            do {
                OS_SpinWaitSysCycles(cycles);
            } while (PMi_SetLEDAsync(value, (PMiCallback)zero, zero) != 0);
        }
    }

return_true:
    return 1;
}
