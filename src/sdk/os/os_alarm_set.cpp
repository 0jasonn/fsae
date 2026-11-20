#include "engine/functions.h"
#include "types.h"

extern "C" u64 OS_GetTick(void);
extern "C" void OSi_InsertAlarm(void *alarm, u64 fire);

// Provisional interpretation: this arms an opaque alarm record. At 0x0201918c,
// +0 is checked and then receives the handler, +4 receives its argument, and
// +0x1c/+0x20 are cleared. The adjacent timer handler at 0x02019208 calls the
// handler at +0 with the argument at +4. This entry saves r1/r2 as low/high delay
// words, r3 as the handler, and the final argument from [sp+0x18], matching a
// CW ABI u64 second parameter.
extern "C" void func_0201918c(void *alarm, u64 delay, void *callback, void *arg) {
    u8 *bytes = (u8 *)alarm;
    u32 irq;
    u64 fire;

    if (alarm == NULL || *(void **)bytes != NULL) {
        OS_Terminate();
    }
    irq = OS_DisableInterrupts();
    *(u32 *)(bytes + 0x1c) = 0;
    *(u32 *)(bytes + 0x20) = 0;
    *(void **)(bytes + 0) = callback;
    *(void **)(bytes + 4) = arg;
    fire = OS_GetTick() + delay;
    OSi_InsertAlarm(alarm, fire);
    OS_RestoreInterrupts(irq);
}
