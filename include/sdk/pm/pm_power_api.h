#ifndef ENGINE_PM_POWER_API_H
#define ENGINE_PM_POWER_API_H

#include "types.h"

typedef void (*PMiCallback)(u32 result, u32 arg);

extern "C" {
s32 func_0201d314(s32 mode, u32 value, s32 force, s32 useSound);
s32 PMi_SetSoundVolume(u32 volume);
s32 PMi_SetLEDAsync(u32 value, PMiCallback callback, u32 arg);
s32 PMi_SetAmp(u32 enabled);
void PMi_WaitVBlank(void);
void OS_SpinWaitSysCycles(u32 cycles);
}

#endif
