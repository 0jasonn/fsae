#ifndef ENGINE_TIMER_ADVANCE_H
#define ENGINE_TIMER_ADVANCE_H

#include "types.h"

// Timer record used by Timer_Advance (src/engine/timer_advance.cpp). Offsets match TimerSnapshot in src/engine/timer.cpp.
typedef struct TimerAdvanceRec {
    u32 owner;                                    // 0x00: first argument of the callback
    u32 flags;                                    // 0x04: bit 12 skips the delta stub
    u8 unk_08[0x10];
    u32 value;                                    // 0x18: live counter, advanced by delta
    u32 lastValue;                                // 0x1c
    u32 limit;                                    // 0x20
    u32 snapshot;                                 // 0x24
    s32 delta;                                    // 0x28
    u8 unk_2c[0x14];
    s32 (*callback)(u32, u32, s32 *, u32);        // 0x40
    u8 unk_44[4];
    u32 callbackArg;                              // 0x48
} TimerAdvanceRec;

extern "C" {
s32 Timer_Advance(TimerAdvanceRec *rec, s32 *deltaOut);
}

#endif
