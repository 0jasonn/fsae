#include "engine/functions.h"
#include "sdk/callees.h"
#include "global.h"
#include "types.h"
#include "sdk/os/os_irq_flush_api.h"
#include "sdk/os/os_switch_api.h"

// Os_IrqDisabledFlush() (0x02017b68): runs Os_ThreadSwitch with interrupts disabled.

void Os_IrqDisabledFlush(void) {
    u32 state;

    state = OS_DisableInterrupts();
    Os_ThreadSwitch();
    OS_RestoreInterrupts(state);
}
