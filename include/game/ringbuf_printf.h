#ifndef GAME_RINGBUF_PRINTF_H
#define GAME_RINGBUF_PRINTF_H

// Declarations used by src/wip/A/ringbuf_printf.cpp.
#include "types.h"
#include "global.h"
#include "sdk/os/os_mutex.h"
#include "sdk/os/os_thread.h"

// Lock record: the word at +0x0c is the owner tag (Task_LockOwnerTag) or the nesting count (Task_LockDepth).
// data_02127420 (0x60 bytes): the mutex that guards the output stream; the rest is not used by the decompiled code.
typedef struct RingBufOutputLock {
    OsMutex mutex;   // 0x00
    u8 unk_18[0x48]; // 0x18
} RingBufOutputLock;

typedef struct LockRecord {
    u8 unk_00[0xc];
    u32 value;     // 0x0c
} LockRecord;

extern "C" {
s32 RingBuf_Printf(const char *fmt, ...);              // RingBuf_Printf
s32 func_020083d0(void *stream, s32 mode);           // parked in scratch/agentA/nonmatching, returns the stream state
s32 func_02007638(void *writer, void *ctx, const u8 *fmt, void *args, s32 flags);   // vprintf core; shared header lacks the fifth parameter
}

extern u8 data_020df628[];      // output stream written by RingBuf_Printf
extern RingBufOutputLock data_02127420;
extern LockRecord Task_LockOwnerTag;      // lock owner record: owner tag at +0x0c
extern LockRecord Task_LockDepth;      // lock depth record: nesting count at +0x0c

#endif
