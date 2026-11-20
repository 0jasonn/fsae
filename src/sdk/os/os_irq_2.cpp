#include "global.h"
#include "types.h"
#include "sdk/os/os_irq.h"
#include "sdk/os/os_irq_state.h"

// Interrupt dispatch stubs: each hardware DMA / NDMA / timer interrupt vectors here and tail-calls OSi_IrqCallback with
// its channel number (0-3 DMA, 4-7 NDMA, 8-11 timers; channel 0 is the function before OSi_IrqDma1).

// Same for a timer channel; its entries follow the DMA / NDMA ones.
void OSi_EnterTimerCallback(u32 channel, void (*callback)(void *), void *argument) {
    irqFunctionTable[channel + 8].callback = callback;
    irqFunctionTable[channel + 8].argument = argument;
    OS_EnableIrqMask(1 << (channel + 3));
    irqFunctionTable[channel + 8].enable = 1;
}

// Master interrupt enable (IME, +0x208), interrupt enable (IE, +0x210) and request flags (IF, +0x214) as one block.
typedef struct IrqControlRegs {
    volatile u16 masterEnable;
    u8 unk_02[6];
    volatile u32 enableMask;
    volatile u32 requestFlags;
} IrqControlRegs;

#define IRQ_CONTROL_REGS ((IrqControlRegs *)0x04000208)

// Each of the four mask helpers runs with IME cleared and returns the previous value of the register it changes.
u32 OS_SetIrqMask(u32 mask) {
    u16 savedMasterEnable = IRQ_CONTROL_REGS->masterEnable;
    IRQ_CONTROL_REGS->masterEnable = 0;
    u32 oldMask = IRQ_CONTROL_REGS->enableMask;
    IRQ_CONTROL_REGS->enableMask = mask;
    IRQ_CONTROL_REGS->masterEnable;
    IRQ_CONTROL_REGS->masterEnable = savedMasterEnable;
    return oldMask;
}

u32 OS_EnableIrqMask(u32 mask) {
    u16 savedMasterEnable = IRQ_CONTROL_REGS->masterEnable;
    IRQ_CONTROL_REGS->masterEnable = 0;
    u32 oldMask = IRQ_CONTROL_REGS->enableMask;
    IRQ_CONTROL_REGS->enableMask = oldMask | mask;
    IRQ_CONTROL_REGS->masterEnable;
    IRQ_CONTROL_REGS->masterEnable = savedMasterEnable;
    return oldMask;
}

u32 OS_DisableIrqMask(u32 mask) {
    u16 savedMasterEnable = IRQ_CONTROL_REGS->masterEnable;
    IRQ_CONTROL_REGS->masterEnable = 0;
    u32 oldMask = IRQ_CONTROL_REGS->enableMask;
    IRQ_CONTROL_REGS->enableMask = oldMask & ~mask;
    IRQ_CONTROL_REGS->masterEnable;
    IRQ_CONTROL_REGS->masterEnable = savedMasterEnable;
    return oldMask;
}

u32 OS_ResetRequestIrqMask(u32 mask) {
    u16 savedMasterEnable = IRQ_CONTROL_REGS->masterEnable;
    IRQ_CONTROL_REGS->masterEnable = 0;
    u32 oldFlags = IRQ_CONTROL_REGS->requestFlags;
    IRQ_CONTROL_REGS->requestFlags = mask;
    IRQ_CONTROL_REGS->masterEnable;
    IRQ_CONTROL_REGS->masterEnable = savedMasterEnable;
    return oldFlags;
}
