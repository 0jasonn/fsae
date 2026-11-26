#include "global.h"
#include "types.h"
#include "sdk/os/device_flags_api.h"
#include "sdk/os/os_boot.h"

extern u32 data_020cd26c[5]; // device type per boot type

u32 OSi_DetectDeviceType(void) {
    return data_020cd26c[OS_GetBootType()];
}

BOOL OS_IsRunOnEmulator(void) {
    if ((Device_InitFlags() & 0x10000000) != 0) {
        return TRUE;
    }
    return FALSE;
}
