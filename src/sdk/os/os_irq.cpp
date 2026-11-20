#include "global.h"
#include "types.h"
#include "sdk/os/os_irq.h"
#include "sdk/os/os_irq_state.h"

// Interrupt dispatch stubs: each hardware DMA / NDMA / timer interrupt vectors here and tail-calls OSi_IrqCallback with
// its channel number (0-3 DMA, 4-7 NDMA, 8-11 timers; channel 0 is the function before OSi_IrqDma1).

void OSi_IrqDma1(void) {
    OSi_IrqCallback(1);
}

void OSi_IrqDma2(void) {
    OSi_IrqCallback(2);
}

void OSi_IrqDma3(void) {
    OSi_IrqCallback(3);
}

void OSi_IrqTimer0(void) {
    OSi_IrqCallback(8);
}

void OSi_IrqTimer1(void) {
    OSi_IrqCallback(9);
}

void OSi_IrqTimer2(void) {
    OSi_IrqCallback(10);
}

void OSi_IrqTimer3(void) {
    OSi_IrqCallback(11);
}

void OSi_IrqNDma0(void) {
    OSi_IrqCallback(4);
}

void OSi_IrqNDma1(void) {
    OSi_IrqCallback(5);
}

void OSi_IrqNDma2(void) {
    OSi_IrqCallback(6);
}

void OSi_IrqNDma3(void) {
    OSi_IrqCallback(7);
}

// Clears the thread queue that OS_WaitIrq sleeps on.
void OS_InitIrqTable(void) {
    data_02fe00a0.tail = NULL;
    data_02fe00a0.head = NULL;
}

// Registers function as the handler for every interrupt source in mask. DMA (bits 8-11), NDMA (28-31) and timer (3-6)
// sources go to the callback table entries 0-3, 4-7 and 8-11; the others to irqCallbackInfo.
void OS_SetIrqFunction(u32 mask, void (*function)(void)) {
    s32 bit;
    s32 index;
    IrqCallbackEntry *entry;

    for (bit = 0; bit < 32; bit++) {
        if (mask & 1) {
            entry = NULL;
            if (bit >= 8 && bit <= 11) {
                index = bit - 8;
                entry = &irqFunctionTable[index];
            } else if (bit >= 28 && bit <= 31) {
                index = bit - 24;
                entry = &irqFunctionTable[index];
            } else if (bit >= 3 && bit <= 6) {
                index = bit + 5;
                entry = &irqFunctionTable[index];
            } else {
                irqCallbackInfo[bit] = function;
            }
            if (entry != NULL) {
                entry->argument = NULL;
                entry->enable = 1;
                entry->callback = (void (*)(void *))function;
            }
        }
        mask >>= 1;
    }
}

// Installs callback for a DMA channel's interrupt and enables it; entry->enable remembers whether it was enabled before.
void OSi_EnterDmaCallback(u32 channel, void (*callback)(void *), void *argument) {
    u32 bit = 1 << (channel + 8);
    irqFunctionTable[channel].callback = callback;
    irqFunctionTable[channel].argument = argument;
    irqFunctionTable[channel].enable = OS_EnableIrqMask(bit) & bit;
}

// Master interrupt enable (IME, +0x208), interrupt enable (IE, +0x210) and request flags (IF, +0x214) as one block.
typedef struct IrqControlRegs {
    volatile u16 masterEnable;
    u8 unk_02[6];
    volatile u32 enableMask;
    volatile u32 requestFlags;
} IrqControlRegs;

#define IRQ_CONTROL_REGS ((IrqControlRegs *)0x04000208)

