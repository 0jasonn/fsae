#include "sdk/os/os_arena.h"
#include "sdk/os/os_irq_state.h"
#include "sdk/os/device_flags_api.h"

// Upper bound of each arena at boot.
void *OS_GetInitArenaHi(s32 id) {
    switch (id) {
    case 0:
        return (void *)0x2f80000;
    case 2:
        if (data_02129b94.hasExtendedMemory == 0) {
            return 0;
        }
        if ((Device_InitFlags() & 0xf) == 4) {
            return 0;
        }
        return (void *)0xdf00000;
    case 3:
        return (void *)0x2000000;
    case 4: {
        u32 dtcm = (u32)&data_02fe0000;
        u32 irqTop = dtcm + 0x3f80 - (u32)SDK_IRQ_STACKSIZE;
        s32 sysStack = (s32)SDK_SYS_STACKSIZE;
        if (sysStack == 0) {
            if (dtcm < 0x2fe0a00) {
                dtcm = 0x2fe0a00;
            }
            return (void *)dtcm;
        }
        if (sysStack < 0) {
            return (void *)(0x2fe0a00 - sysStack);
        }
        return (void *)(irqTop - sysStack);
    }
    case 5:
        return (void *)0x2fff680;
    case 6:
        return (void *)0x3040000;
    default:
        return 0;
    }
}
