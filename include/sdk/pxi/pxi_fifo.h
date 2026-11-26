#ifndef SDK_PXI_PXI_FIFO_H
#define SDK_PXI_PXI_FIFO_H

// TwlSDK PXI FIFO: tagged words sent between the ARM9 and the ARM7 (5-bit tag, error flag, 26-bit payload).
#include "types.h"

// Receive callback installed per tag: the tag, the 26-bit payload and the error flag.
typedef void (*PxiFifoCallback)(u32 tag, u32 data, s32 err);

extern "C" {
void Engine_Relay0201a070(void); // tail call to func_0201a070 (src/sdk/pxi/engine_relay.cpp)
s32 PXI_IsCallbackReady(u32 tag, u32 proc);
s32 PXI_SendWordByFifo(u32 tag, u32 data, u32 err);

// Not decompiled yet.
void func_0201a070(void);
void PXI_SetFifoRecvCallback(u32 tag, PxiFifoCallback callback);
}

#endif
