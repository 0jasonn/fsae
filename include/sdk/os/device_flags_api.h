#ifndef SDK_OS_DEVICE_FLAGS_API_H
#define SDK_OS_DEVICE_FLAGS_API_H

// TwlSDK console type: Device_InitFlags (src/sdk/os/device_flags.cpp) caches it, OSi_DetectDeviceType and
// OS_IsRunOnEmulator follow it in the ROM.

#include "engine/entity.h"

extern "C" {
u32 Device_InitFlags(void);
u32 OSi_DetectDeviceType(void);
BOOL OS_IsRunOnEmulator(void);
}

#endif
