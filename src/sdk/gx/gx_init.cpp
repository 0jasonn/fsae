#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/gx/gx.h"
#include "sdk/gx/gx.h"
#include "sdk/gx/gx_vramcnt.h"
#include "sdk/os/os_lock.h"
#include "sdk/os/os_terminate.h"
#include "sdk/mi/mi_dma.h"
#include "sdk/mi/mi_memory.h"

void GX_Init(void) {
    s32 lockId;

    *(volatile u16 *)0x04000304 |= 0x8000;
    *(volatile u16 *)0x04000304 = (*(volatile u16 *)0x04000304 & ~0x20e) | 0xe | 0x200;
    *(volatile u16 *)0x04000304 |= 1;
    GX_InitGXState();
    if ((&data_02129824)[1] == 0) {
        do {
            lockId = OS_GetLockID();
            if (lockId == -3) {
                OS_Terminate();
            }
            (&data_02129824)[1] = lockId;
        } while ((&data_02129824)[1] == 0);
    }
    *(volatile u16 *)0x04000004 = 0;
    *(volatile u32 *)0x04000000 = 0;
    if (data_020dfb7c.defaultDma != -1) {
        if ((u32)data_020dfb7c.defaultDma > 3) {
            func_02189350(data_020dfb7c.defaultDma - 4, (void *)0x04000008, 0, 0x60);
            *(volatile u16 *)0x0400006c = 0;
            func_02189350(data_020dfb7c.defaultDma - 4, (void *)0x04001000, 0, 0x70);
        } else {
            MIi_DmaFill32(data_020dfb7c.defaultDma, (void *)0x04000008, 0, 0x60, 1);
            *(volatile u16 *)0x0400006c = 0;
            MIi_DmaFill32(data_020dfb7c.defaultDma, (void *)0x04001000, 0, 0x70, 1);
        }
    } else {
        OSi_CpuClear32(0, (void *)0x04000008, 0x60);
        *(volatile u16 *)0x0400006c = 0;
        OSi_CpuClear32(0, (void *)0x04001000, 0x70);
    }
    *(volatile u16 *)0x04000020 = 0x100;
    *(volatile u16 *)0x04000026 = 0x100;
    *(volatile u16 *)0x04000030 = 0x100;
    *(volatile u16 *)0x04000036 = 0x100;
    *(volatile u16 *)0x04001020 = 0x100;
    *(volatile u16 *)0x04001026 = 0x100;
    *(volatile u16 *)0x04001030 = 0x100;
    *(volatile u16 *)0x04001036 = 0x100;
}
