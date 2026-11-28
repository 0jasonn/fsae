#ifndef SDK_MI_MI_DMA_H
#define SDK_MI_MI_DMA_H

// TwlSDK MI DMA: channel registers at 0x040000b0 + 12 * dmaNo (source, destination, control). The Copy/Fill calls wait
// for the channel, program it through func_01ff8020 and (except the Async ones) wait for the end. flag selects the
// immediate-start variant.
#include "types.h"

extern "C" {
void MIi_DmaFill32(u32 dmaNo, void *dest, u32 data, u32 size, u32 flag);
void MIi_DmaCopy32(u32 dmaNo, const void *src, void *dest, u32 size, u32 flag);
void MIi_DmaCopy16(u32 dmaNo, const void *src, void *dest, u32 size, u32 flag);
void MIi_DmaCopy32Async(u32 dmaNo, const void *src, void *dest, u32 size, void (*callback)(void *), void *argument,
                        u32 flag);
void MI_WaitDma(u32 dmaNo);
void MI_HBlankDmaCopy16(u32 dmaNo, const void *src, void *dest, u32 size);
void OS_StopTimer64(void); // stops DMA channels 0-3 (dsd name)
void MIi_CardDmaCopy32(u32 dmaNo, const void *src, void *dest, u32 size);
void MI_Init(void);
// Not decompiled yet.
void MI_StopDma(u32 dmaNo);
void func_01ff8020(u32 dmaNo, u32 src, u32 dest, u32 control, u32 mode); // ITCM: programs one DMA channel
}

// src/sdk/mi/region_check.cpp (C++ linkage).
void Region_CheckNotIoOrRom(u32 flags, u32 addr, u32 len, u32 dir);

#endif
