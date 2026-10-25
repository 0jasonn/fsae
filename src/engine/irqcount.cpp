#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/callees.h"

// Interrupt-protected counter at data_0212991c (its count is at +4). Acquire takes a slot while the count is below
// 0xffffffff, release gives one back while it is not zero; both return the old count.
typedef struct IrqCountWork {
    u32 unk_00;
    u32 count;
} IrqCountWork;

extern IrqCountWork data_0212991c;

extern "C" void Os_EnableIrqAndHalt(void);
extern "C" u32 IrqCount_Acquire(void);
extern "C" u32 IrqCount_Release(void);
extern "C" void Obj_SetWordB4(void *obj, u32 value);

ARM void Os_EnableIrqAndHalt(void) {
    OS_EnableInterrupts();
    for (;;) {
        OS_Halt();
    }
}

ARM u32 IrqCount_Acquire(void) {
    u32 state = OS_DisableInterrupts();
    u32 old;
    if (data_0212991c.count < 0xffffffff) {
        old = data_0212991c.count;
        data_0212991c.count = old + 1;
    }
    OS_RestoreInterrupts(state);
    return old;
}

ARM u32 IrqCount_Release(void) {
    u32 state = OS_DisableInterrupts();
    u32 old = 0;
    if (data_0212991c.count != 0) {
        old = data_0212991c.count;
        data_0212991c.count = old - 1;
    }
    OS_RestoreInterrupts(state);
    return old;
}

ARM void Obj_SetWordB4(void *obj, u32 value) {
    *(u32 *)((u8 *)obj + 0xb4) = value;
}
