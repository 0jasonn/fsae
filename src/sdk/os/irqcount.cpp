#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/os/irqcount_api.h"
#include "sdk/os/os_halt_api.h"
#include "sdk/os/os_thread.h"

// Scheduler disable count (data_0212991c.busy): Acquire takes a slot while the count is below 0xffffffff, release gives
// one back while it is not zero; both return the old count.

void Os_EnableIrqAndHalt(void) {
    OS_EnableInterrupts();
    for (;;) {
        OS_Halt();
    }
}

u32 IrqCount_Acquire(void) {
    u32 state = OS_DisableInterrupts();
    u32 old;
    if (data_0212991c.busy < 0xffffffff) {
        old = data_0212991c.busy;
        data_0212991c.busy = old + 1;
    }
    OS_RestoreInterrupts(state);
    return old;
}

u32 IrqCount_Release(void) {
    u32 state = OS_DisableInterrupts();
    u32 old = 0;
    if (data_0212991c.busy != 0) {
        old = data_0212991c.busy;
        data_0212991c.busy = old - 1;
    }
    OS_RestoreInterrupts(state);
    return old;
}

void Obj_SetWordB4(void *obj, u32 value) {
    *(u32 *)((u8 *)obj + 0xb4) = value;
}
