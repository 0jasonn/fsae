#ifndef SDK_OS_OS_IRQ_H
#define SDK_OS_OS_IRQ_H

#include "types.h"

extern "C" {
void OSi_IrqCallback(u32 channel);
void OSi_IrqDma1(void);
void OSi_IrqDma2(void);
void OSi_IrqDma3(void);
void OSi_IrqTimer0(void);
void OSi_IrqTimer1(void);
void OSi_IrqTimer2(void);
void OSi_IrqTimer3(void);
void OSi_IrqNDma0(void);
void OSi_IrqNDma1(void);
void OSi_IrqNDma2(void);
void OSi_IrqNDma3(void);
void OS_InitIrqTable(void);
void OSi_EnterDmaCallback(u32 channel, void (*callback)(void *), void *argument);
void OSi_EnterTimerCallback(u32 channel, void (*callback)(void *), void *argument);
u32 OS_SetIrqMask(u32 mask);
u32 OS_EnableIrqMask(u32 mask);
u32 OS_DisableIrqMask(u32 mask);
u32 OS_ResetRequestIrqMask(u32 mask);
void OS_SetIrqStackChecker(void);
void OS_WaitIrq(u32 clear, u32 irqFlags);
void Os_LinkThreadAndFlush(void *queue);
u32 OS_DisableInterrupts(void);
u32 OS_RestoreInterrupts(u32 state);
}

// C++ linkage (symbols.txt: _Z17OS_SetIrqFunctionmPFvvE).
void OS_SetIrqFunction(u32 mask, void (*function)(void));

#endif
