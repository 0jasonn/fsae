#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/pm/pm.h"

// PMi_SendSleepStart(mode, param) (0x0201cbc0): sends the sleep-start request (a bare command word, then the command
// with its mode and parameter) once the LCD power state has been applied.
s32 PMi_SendSleepStart(u32 mode, u32 param) {
    u32 words[2];

    words[0] = 0x3006000;
    PMi_TryToSendPxiDataTillSuccess(words, 1);
    while (func_0201d314(0, 2, 0, 1) != 1) {
    }
    words[0] = (mode & 0xff) | 0x2006200;
    words[1] = 0x1010000 | (u16)param;
    PMi_TryToSendPxiDataTillSuccess(words, 2);
    return 0;
}

// PM_SendUtilityCommandAsync(number, parameter, retValue, callback, arg) (0x0201cc4c): queues PM utility command number
// with a 16-bit parameter; retValue receives the reply and callback(result, arg) runs when it arrives.
s32 PM_SendUtilityCommandAsync(u32 number, u32 parameter, u16 *retValue, PMiCallback callback, u32 arg) {
    u32 words[2];

    words[0] = (number & 0xff) | 0x2006100;
    words[1] = 0x1010000 | (u16)parameter;
    return PMi_StartSendBlock(words, 2, (u32)retValue, (u32)callback, arg);
}

// PM_SendUtilityCommand(number, parameter, retValue) (0x0201cc94): synchronous version; returns the send error or the
// callback result.
s32 PM_SendUtilityCommand(u32 number, u32 parameter, u16 *retValue) {
    u32 result;
    s32 error = PM_SendUtilityCommandAsync(number, parameter, retValue, (PMiCallback)PMi_DummyCallback, (u32)&result);

    if (error != 0) {
        return error;
    }
    PMi_WaitBusy();
    return result;
}

// PMi_SetLEDAsync(value, callback, arg) (0x0201cccc): maps the LED mode (1, 2, 3) to its PM command (1, 3, 2) and sends
// it. Returns 0xffff for an unknown mode.
s32 PMi_SetLEDAsync(u32 value, PMiCallback callback, u32 arg) {
    u32 command;

    switch (value) {
    case 1:
        command = 1;
        break;
    case 3:
        command = 2;
        break;
    case 2:
        command = 3;
        break;
    default:
        command = 0;
        break;
    }
    if (command == 0) {
        return 0xffff;
    }
    return PM_SendUtilityCommandAsync(command, 0, NULL, callback, arg);
}

// PMi_SetSoundVolume(value) (0x0201cd30): synchronous PMi_SetLEDAsync.
s32 PMi_SetSoundVolume(u32 value) {
    u32 result;
    s32 error = PMi_SetLEDAsync(value, (PMiCallback)PMi_DummyCallback, (u32)&result);

    if (error != 0) {
        return error;
    }
    PMi_WaitBusy();
    return result;
}

// PM_SetBackLightAsync(target, on, callback, arg) (0x0201cd58): switches the backlight of a screen (0 = both, 1 = top,
// 2 = bottom) on or off. Returns 0xffff for an invalid target or state.
s32 PM_SetBackLightAsync(u32 target, u32 on, PMiCallback callback, u32 arg) {
    u32 command = 0;

    if (target == 0) {
        if (on == 1) {
            command = 6;
        }
        if (on == 0) {
            command = 7;
        }
    } else if (target == 1) {
        if (on == 1) {
            command = 4;
        }
        if (on == 0) {
            command = 5;
        }
    } else if (target == 2) {
        if (on == 1) {
            command = 8;
        }
        if (on == 0) {
            command = 9;
        }
    }
    if (command == 0) {
        return 0xffff;
    }
    return PM_SendUtilityCommandAsync(command, 0, NULL, callback, arg);
}

// PM_SetBackLight(target, on) (0x0201cde0): synchronous PM_SetBackLightAsync.
s32 PM_SetBackLight(u32 target, u32 on) {
    u32 result;
    s32 error = PM_SetBackLightAsync(target, on, (PMiCallback)PMi_DummyCallback, (u32)&result);

    if (error != 0) {
        return error;
    }
    PMi_WaitBusy();
    return result;
}

// PM_ForceToPowerOffAsync(callback, arg) (0x0201ce08): starts the forced power off: marks the PM state, avoids an LCD
// reset, runs the pre-power-off callback list and sends command 0xe.
s32 PM_ForceToPowerOffAsync(PMiCallback callback, u32 arg) {
    data_0212b920.lcdPowerState = 3;
    PMi_LCDOnAvoidReset();
    PMi_ExecuteList(PM_FORCE_OFF_CALLBACK_LIST);
    return PM_SendUtilityCommandAsync(0xe, 0, NULL, callback, arg);
}

// PMi_ForceToPowerOff() (0x0201ce54): synchronous PM_ForceToPowerOffAsync; the PXI wait flags are set to poll while it
// waits.
s32 PMi_ForceToPowerOff(void) {
    volatile u32 result;
    s32 error = PM_ForceToPowerOffAsync((PMiCallback)PMi_DummyCallback, (u32)&result);

    if (error != 0) {
        return error;
    }
    data_020dfbe4 = 0xc;
    PMi_WaitBusy();
    data_020dfbe4 = 2;
    return result;
}
