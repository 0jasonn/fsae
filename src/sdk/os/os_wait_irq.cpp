#include "global.h"
#include "types.h"
#include "sdk/os/os_irq.h"
#include "sdk/os/os_irq_state.h"

// OS_WaitIrq(clear, irqFlags): with interrupts off, optionally clears irqFlags in the IRQ-check word, then sleeps on the
// IRQ thread queue until one of the flags has been set by an interrupt handler.
void OS_WaitIrq(u32 clear, u32 irqFlags) {
    u32 state = OS_DisableInterrupts();
    if (clear != 0) {
        OS_IRQ_CHECK_FLAG &= ~irqFlags;
    }
    while ((irqFlags & OS_IRQ_CHECK_FLAG) == 0) {
        Os_LinkThreadAndFlush(&data_02fe00a0);
    }
    OS_RestoreInterrupts(state);
}
