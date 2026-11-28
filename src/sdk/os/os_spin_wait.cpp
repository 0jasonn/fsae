#include "engine/functions.h"
#include "sdk/os/os_interrupts.h"
#include "sdk/os/os_irq.h"

// Busy waits.
void OS_SpinWaitSysCycles(u32 cycles) {
    u32 shift;
    if ((*(volatile u16 *)0x4004004 & 1) == 1) {
        shift = 2;
    } else {
        shift = 1;
    }
    cycles <<= shift;
    if (cycles > 0x10) {
        OS_SpinWaitCpuCycles(cycles - 0x10);
    }
}

void OS_WaitVBlankIntr(void) {
    WaitByLoop(1);
    OS_WaitIrq(1, 1);
}
