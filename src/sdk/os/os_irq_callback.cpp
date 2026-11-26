#include "global.h"
#include "types.h"
#include "sdk/os/os_irq.h"
#include "sdk/os/os_irq_state.h"

// Common interrupt handler body for the DMA / NDMA / timer stubs (OSi_IrqDma0..OSi_IrqTimer3): takes the registered callback
// out of its table entry (one-shot), runs it, marks the interrupt in the IRQ-check word and, unless the entry asked to stay
// enabled, masks the source again. Follows OS_WaitIrq in the ROM (0x02016c80).
void OSi_IrqCallback(u32 channel) {
    void (*callback)(void *);
    u32 irqBit;
    irqBit = 1 << data_020dfb84[channel];
    callback = irqFunctionTable[channel].callback;
    irqFunctionTable[channel].callback = NULL;
    if (callback != NULL) {
        callback(irqFunctionTable[channel].argument);
    }
    OS_IRQ_CHECK_FLAG |= irqBit;
    if (irqFunctionTable[channel].enable == 0) {
        OS_DisableIrqMask(irqBit);
    }
}
