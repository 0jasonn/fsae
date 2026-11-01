#include "engine/functions.h"
#include "engine/callees.h"
#include "global.h"
#include "types.h"
#include "engine/os_irq_flush_api.h"
#include "engine/os_switch_api.h"

// Os_IrqDisabledFlush() (0x02017b68): runs Os_ThreadSwitch with interrupts disabled.

void Os_IrqDisabledFlush(void) {
    u32 state;

    state = OS_DisableInterrupts();
    Os_ThreadSwitch();
    OS_RestoreInterrupts(state);
}
