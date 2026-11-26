#include "global.h"
#include "types.h"
#include "sdk/os/os_event.h"
#include "sdk/os/os_interrupts.h"
#include "sdk/os/os_irq.h"

// mode 0 waits until all bits of pattern are set, mode 1 until any is; the bits in clearBits are then cleared. Returns
// the flags seen (0 for an unknown mode).
u32 OS_WaitEventEx(OsEvent *event, u32 pattern, u32 mode, u32 clearBits) {
    u32 result = 0;
    u32 state = OS_DisableInterrupts();

    switch (mode) {
    case 0:
        while ((event->flags & pattern) != pattern) {
            Os_LinkThreadAndFlush(&event->queue);
        }
        result = event->flags;
        break;
    case 1:
        while ((event->flags & pattern) == 0) {
            Os_LinkThreadAndFlush(&event->queue);
        }
        result = event->flags;
        break;
    }
    if (result != 0) {
        event->flags &= ~clearBits;
    }
    OS_RestoreInterrupts(state);
    return result;
}

void OS_SignalEvent(OsEvent *event, u32 flags) {
    u32 state = OS_DisableInterrupts();
    if (flags != 0) {
        event->flags |= flags;
        OS_WakeupThread(&event->queue);
    }
    OS_RestoreInterrupts(state);
}

void OS_ClearEvent(OsEvent *event, u32 flags) {
    u32 state = OS_DisableInterrupts();
    event->flags &= ~flags;
    OS_RestoreInterrupts(state);
}
