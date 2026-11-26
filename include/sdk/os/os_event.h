#ifndef SDK_OS_OS_EVENT_H
#define SDK_OS_OS_EVENT_H

// TwlSDK OS events: flag bits with a wait queue behind them.
#include "types.h"
#include "sdk/os/os_thread.h"

typedef struct OsEvent {
    volatile u32 flags;  // 0x00
    OsThreadQueue queue; // 0x04
} OsEvent;

extern "C" {
void OS_InitEvent(OsEvent *event);
u32 Os_WaitEventExWrap(OsEvent *event, u32 pattern, u32 mode); // OS_WaitEventEx with no bits to clear
u32 OS_WaitEventEx(OsEvent *event, u32 pattern, u32 mode, u32 clearBits);
void OS_SignalEvent(OsEvent *event, u32 flags);
void OS_ClearEvent(OsEvent *event, u32 flags);
}

#endif
