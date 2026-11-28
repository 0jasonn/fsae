#ifndef SDK_PXI_PXI_FIFO_H
#define SDK_PXI_PXI_FIFO_H

// TwlSDK PXI FIFO: tagged words sent between the ARM9 and the ARM7 (5-bit tag, error flag, 26-bit payload).
#include "types.h"

// Receive callback installed per tag: the tag, the 26-bit payload and the error flag.
typedef void (*PxiFifoCallbackFn)(u32 tag, u32 data, s32 err);

// System work shared with the ARM7 at 0x02fffc00: the masks of tags that have a receive callback installed, one per processor.
typedef struct PxiSharedWork {
    u8 unk_000[0x388];
    u32 callbackMask[2]; // 0x388: ARM9, ARM7
} PxiSharedWork;

#define PXI_SHARED_WORK ((PxiSharedWork *)0x02fffc00)

// data_02129ccc: set once PXI_Init has run. data_02129cd0: receive callback of each of the 32 tags.
extern u16 data_02129ccc;
extern PxiFifoCallbackFn data_02129cd0[32];

extern "C" {
void Engine_Relay0201a070(void); // tail call to PXI_Init (src/sdk/pxi/engine_relay.cpp)
s32 PXI_IsCallbackReady(u32 tag, u32 proc);
s32 PXI_SendWordByFifo(u32 tag, u32 data, u32 err);

void PXI_Init(void);

// Not decompiled yet.
void PXI_SetFifoRecvCallback(u32 tag, PxiFifoCallbackFn callback);
void PXIi_HandlerRecvFifoNotEmpty(void);
}

#endif
