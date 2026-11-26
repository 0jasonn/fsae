#ifndef SDK_OS_OS_BOOT_H
#define SDK_OS_OS_BOOT_H

// TwlSDK OS boot information (the boot info block in the shared area at 0x02fffc40).
#include "types.h"

extern "C" {
u32 OS_GetBootType(void);
void *OS_GetBootInfo(void);
}

#endif
