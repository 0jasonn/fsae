#include "sdk/mi/mi_dma.h"
#include "sdk/os/os_interrupts.h"
#include "sdk/os/os_irq.h"

typedef volatile u32 vu32;

// MI DMA helpers: the Copy/Fill calls wait for the channel, program it through func_01ff8020 and wait for the end.

void MIi_DmaFill32(u32 dmaNo, void *dest, u32 data, u32 size, u32 flag) {
    volatile u32 *control;

    if (size == 0) {
        return;
    }
    control = (volatile u32 *)(0x4000000 + (dmaNo * 3 + 2) * 4 + 0xb0);
    while (*control & 0x80000000) {
    }
    if (flag) {
        func_01ff8020(dmaNo, data, (u32)dest, (size >> 2) | 0x85000000, 0x12);
    } else {
        func_01ff8020(dmaNo, data, (u32)dest, (size >> 2) | 0x05000000, 0x16);
    }
    while (*control & 0x80000000) {
    }
}

void MIi_DmaCopy32(u32 dmaNo, const void *src, void *dest, u32 size, u32 flag) {
    volatile u32 *control;

    if (size == 0) {
        return;
    }
    Region_CheckNotIoOrRom(dmaNo, (u32)src, size, 0);
    control = (volatile u32 *)(0x4000000 + (dmaNo * 3 + 2) * 4 + 0xb0);
    while (*control & 0x80000000) {
    }
    if (flag) {
        func_01ff8020(dmaNo, (u32)src, (u32)dest, (size >> 2) | 0x84000000, 2);
    } else {
        func_01ff8020(dmaNo, (u32)src, (u32)dest, (size >> 2) | 0x04000000, 6);
    }
    while (*control & 0x80000000) {
    }
}

void MIi_DmaCopy16(u32 dmaNo, const void *src, void *dest, u32 size, u32 flag) {
    volatile u32 *control;

    if (size == 0) {
        return;
    }
    Region_CheckNotIoOrRom(dmaNo, (u32)src, size, 0);
    control = (volatile u32 *)(0x4000000 + (dmaNo * 3 + 2) * 4 + 0xb0);
    while (*control & 0x80000000) {
    }
    if (flag) {
        func_01ff8020(dmaNo, (u32)src, (u32)dest, (size >> 1) | 0x80000000, 2);
    } else {
        func_01ff8020(dmaNo, (u32)src, (u32)dest, size >> 1, 6);
    }
    while (*control & 0x80000000) {
    }
}

void MIi_DmaCopy32Async(u32 dmaNo, const void *src, void *dest, u32 size, void (*callback)(void *), void *argument,
                        u32 flag) {
    Region_CheckNotIoOrRom(dmaNo, (u32)src, size, 0);
    if (size == 0) {
        if (callback) {
            callback(argument);
        }
        return;
    }
    MI_WaitDma(dmaNo);
    if (callback) {
        OSi_EnterDmaCallback(dmaNo, callback, argument);
        if (flag) {
            func_01ff8020(dmaNo, (u32)src, (u32)dest, (size >> 2) | 0xc4000000, 0);
        } else {
            func_01ff8020(dmaNo, (u32)src, (u32)dest, (size >> 2) | 0x44000000, 4);
        }
    } else {
        if (flag) {
            func_01ff8020(dmaNo, (u32)src, (u32)dest, (size >> 2) | 0x84000000, 0);
        } else {
            func_01ff8020(dmaNo, (u32)src, (u32)dest, (size >> 2) | 0x04000000, 4);
        }
    }
}

void MI_WaitDma(u32 dmaNo) {
    u32 irq = OS_DisableInterrupts();
    vu32 *control = (vu32 *)(0x4000000 + dmaNo * 12 + 0xb8);
    while (*control & 0x80000000) {
    }
    if (dmaNo == 0) {
        vu32 *p = (vu32 *)(0x4000000 + (dmaNo * 12 + 0xb0));
        *(vu32 *)(0x4000000 + dmaNo * 12 + 0xb0) = 0;
        p[1] = 0;
        p[2] = 0x81400001;
    }
    OS_RestoreInterrupts(irq);
}
