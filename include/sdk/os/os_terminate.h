#ifndef SDK_OS_OS_TERMINATE_H
#define SDK_OS_OS_TERMINATE_H

// TwlSDK OS_Terminate: shuts the system down (callback, FAT unmount, PXI notification) and halts.
#include "types.h"

// data_02129cc0: termination hook and state.
typedef struct OsTerminateState {
    void *callbackArg;            // 0x00
    void (*callback)(void *);     // 0x04: one-shot hook run before the shutdown
    u32 terminating;              // 0x08: set once the shutdown has started
} OsTerminateState;

extern OsTerminateState data_02129cc0;

extern "C" {
void OS_Terminate(void);
}

#endif
