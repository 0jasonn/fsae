#ifndef SDK_OS_OS_PROTECTION_H
#define SDK_OS_OS_PROTECTION_H

// TwlSDK OS CP15 helpers: DTCM and the protection unit (MPU) regions.
#include "types.h"

extern void (*data_020dfba4[8])(u32 value);  // Mpu_SetRegion0..7 (sdk/os/mpu_api.h), by region

extern "C" {
void OS_EnableDTCM(void);
u32 OS_GetDTCMAddress(void);
void OS_EnableProtectionUnit(void);
void OS_DisableProtectionUnit(void);
void OS_SetProtectionRegionParam(u32 region, u32 value);
void OS_SetProtectionRegionEx(u32 region, u32 address, u32 size); // size: region size code (0x16 = 4 KB ...)
}

#endif
