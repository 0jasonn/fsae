#ifndef SDK_OS_OS_TICK_H
#define SDK_OS_OS_TICK_H

// TwlSDK OS tick counter (timer 0).
#include "types.h"

// data_02129c60: tick counter state. The high part of the 48-bit tick count is kept shifted at +8.
typedef struct OsTickState {
    u16 initialised; // 0x00
    u8 unk_02[6];    // 0x02
    u64 counter;     // 0x08
} OsTickState;

extern OsTickState data_02129c60;
extern volatile u64 data_02129c68; // same bytes as data_02129c60.counter; OS_GetLowEntropyData reads it as a symbol of its own

extern "C" {
u16 OS_GetTickLo(void);
u64 OS_GetTick(void);
}

#endif
