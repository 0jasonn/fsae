#ifndef WIP_A_RINGBUF_PRINTF_H
#define WIP_A_RINGBUF_PRINTF_H

// Declarations used by src/wip/A/ringbuf_printf.cpp.
#include "types.h"
#include "global.h"

// Lock record: the word at +0x0c is the owner tag (Task_LockOwnerTag) or the nesting count (Task_LockDepth).
typedef struct LockRecord {
    u8 unk_00[0xc];
    u32 value;     // 0x0c
} LockRecord;

extern "C" {
s32 RingBuf_Printf(const char *fmt, ...);              // RingBuf_Printf
s32 func_020083d0(void *stream, s32 mode);           // parked in scratch/agentA/nonmatching, returns the stream state
s32 Sub_CallChecked(s32 a, s32 b, s32 c);            // src/engine/stream.cpp (Sub_CallChecked)
s32 func_02007638(void *writer, void *ctx, const u8 *fmt, void *args, s32 flags);   // vprintf core; shared header lacks the fifth parameter
void OS_LockMutexFromWToR(void *mutex);
void OS_UnlockMutex(void *mutex);
}

extern u8 data_020df628[];      // output stream written by RingBuf_Printf
extern u8 data_02127420[];      // mutex that guards the output stream
extern LockRecord Task_LockOwnerTag;      // lock owner record: owner tag at +0x0c
extern LockRecord Task_LockDepth;      // lock depth record: nesting count at +0x0c
extern u32 data_02129938[];     // word 1 holds the current OSThread pointer

#endif
