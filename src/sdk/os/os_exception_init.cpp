#include "sdk/os/os_exception.h"
#include "sdk/os/os_protection.h"

// Protection region setter with the size-dependent mask, and exception handler set-up.
void OS_SetProtectionRegionEx(u32 region, u32 address, u32 size) {
    u32 mask = 0xfffff000 << ((size - 0x16) >> 1);
    OS_SetProtectionRegionParam(region, size | (address & mask) | 1);
}

void OS_InitException(void) {
    u32 valid = 0;
    u32 handler = *(u32 *)0x2fffd9c;

    data_02129bc0.sharedHandler = handler;
    if (handler >= 0x2600000) {
        if (handler < 0x2800000) {
            valid = 1;
        }
    }
    if (valid == 0) {
        handler = 0;
    }
    data_02129bc0.handler = handler;
    if (handler == 0) {
        *(u32 *)0x2fffd9c = (u32)OSi_ExceptionHandler;
    }
    data_02129bc0.enabled = 0;
}
