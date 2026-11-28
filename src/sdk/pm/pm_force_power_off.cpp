#include "global.h"
#include "types.h"
#include "sdk/os/os_interrupts.h"
#include "sdk/os/os_halt_api.h"
#include "sdk/mi/mi_dma.h"
#include "sdk/pm/pm.h"

void PM_ForceToPowerOff(void) {
    while (PMi_ForceToPowerOff() != 0) {
        OS_SpinWaitSysCycles(0x51d23);
    }
    OS_DisableInterrupts();
    OS_StopTimer64();
    func_021894e4();
    while (1) {
        OS_Halt();
    }
}
