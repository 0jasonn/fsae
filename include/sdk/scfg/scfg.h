#ifndef SDK_SCFG_SCFG_H
#define SDK_SCFG_SCFG_H

// TwlSDK SCFG library: 64-bit values requested from the ARM7 over the PXI FIFO (tag 0x17).
#include "types.h"

// data_02129d78: state of the pending request (0x18 bytes), addressed as words by the ROM code (a struct view changes the
// generated code of the receive callback):
//   [0] busy: nonzero while a request is in flight
//   [1], [2] the 64-bit reply (low, high), collected in four 16-bit pieces
//   [3] bit per piece received so far (0xf when complete)
//   [4] callback, void (*)(u64 value, void *arg)
//   [5] callback argument
extern u32 data_02129d78[6];

extern "C" {
void SCFG_Init(void);
void func_0201aa78(u32 tag, u32 data, s32 err); // PXI receive callback installed by SCFG_Init (src/sdk/scfg/pxi_receive64.cpp)
}

#endif
