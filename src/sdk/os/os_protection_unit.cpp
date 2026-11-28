#include "sdk/os/os_protection.h"

// CP15 control helpers (DTCM, protection unit) and the region parameter dispatcher.
asm void OS_EnableDTCM(void) {
    mrc p15, 0, r0, c1, c0, 0
    orr r0, r0, #0x10000
    mcr p15, 0, r0, c1, c0, 0
    bx lr
}

asm u32 OS_GetDTCMAddress(void) {
    mrc p15, 0, r0, c9, c1, 0
    ldr r1, =0xfffff000
    and r0, r0, r1
    bx lr
}

asm void OS_EnableProtectionUnit(void) {
    mrc p15, 0, r0, c1, c0, 0
    orr r0, r0, #0x1
    mcr p15, 0, r0, c1, c0, 0
    bx lr
}

asm void OS_DisableProtectionUnit(void) {
    mrc p15, 0, r0, c1, c0, 0
    bic r0, r0, #0x1
    mcr p15, 0, r0, c1, c0, 0
    bx lr
}

void OS_SetProtectionRegionParam(u32 region, u32 value) {
    data_020dfba4[region](value);
}
