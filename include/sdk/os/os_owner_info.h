#ifndef SDK_OS_OS_OWNER_INFO_H
#define SDK_OS_OS_OWNER_INFO_H

// TwlSDK OS owner information (the console's user settings and MAC address in the shared area).
#include "types.h"

extern "C" {
void OS_GetMacAddress(u8 *dest);
}

#endif
