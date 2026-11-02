#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "game/ringbuf_printf.h"

// Thread record at the current OSThread pointer (data_02129938[1]). Only the lock tag is named.
typedef struct LockThread {
    u8 unk_00[0x6c];
    u32 lockTag;   // 0x6c: identifies the owner of the output lock
} LockThread;

// RingBuf_Printf(fmt, ...) (RingBuf_Printf): formats fmt and the arguments after it into data_020df628 through
// Sub_CallChecked. The output mutex is held for the whole call. Task_LockDepth counts the nested calls of the owning
// thread, and Task_LockOwnerTag holds that thread's tag. Returns -1 when the stream is not writable.
s32 RingBuf_Printf(const char *fmt, ...) {
    s32 result;

    if (func_020083d0(data_020df628, -1) >= 0) {
        return -1;
    }
    if (OS_TryLockMutex(data_02127420) == 0) {
        Task_LockOwnerTag.value = ((LockThread *)data_02129938[1])->lockTag;
        Task_LockDepth.value = 1;
    } else {
        if (Task_LockOwnerTag.value == ((LockThread *)data_02129938[1])->lockTag) {
            Task_LockDepth.value += 1;
        } else {
            OS_LockMutexFromWToR(data_02127420);
            Task_LockOwnerTag.value = ((LockThread *)data_02129938[1])->lockTag;
            Task_LockDepth.value = 1;
        }
    }
    result = func_02007638((void *)Sub_CallChecked, data_020df628, (const u8 *)fmt, (u8 *)(((u32)&fmt) & ~3) + 4, 0);
    Task_LockDepth.value -= 1;
    if (Task_LockDepth.value == 0) {
        OS_UnlockMutex(data_02127420);
    }
    return result;
}
