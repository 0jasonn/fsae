#include "engine/functions.h"
#include "engine/callees.h"
#include "global.h"
#include "types.h"

// Os_IrqDisabledFlush() (0x02017b68): runs Os_ThreadSwitch with interrupts disabled.
extern "C" void Os_IrqDisabledFlush(void);
extern "C" void Os_ThreadSwitch(void);

void Os_IrqDisabledFlush(void) {
    u32 state;

    state = OS_DisableInterrupts();
    Os_ThreadSwitch();
    OS_RestoreInterrupts(state);
}
