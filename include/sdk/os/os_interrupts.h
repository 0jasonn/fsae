#ifndef SDK_OS_OS_INTERRUPTS_H
#define SDK_OS_OS_INTERRUPTS_H

#include "types.h"

extern "C" {
u32 OS_EnableInterrupts(void);
u32 OS_DisableInterrupts(void);
u32 OS_RestoreInterrupts(u32 state);
u32 OS_DisableInterrupts_IrqAndFiq(void);
u32 OS_RestoreInterrupts_IrqAndFiq(u32 state);
u32 OS_GetCpsrIrq(void);
u32 OS_GetProcMode(void);
void OS_SpinWaitCpuCycles(u32 cycles);
}

#endif
