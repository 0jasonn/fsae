#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/os/os_interrupts.h"
#include "sdk/pm/pm.h"
#include "sdk/pxi/pxi_fifo.h"

// PMi_WaitBusy() (0x0201c7c4): waits for the outstanding PM request to finish. When interrupts cannot deliver the
// reply (IRQ mode, IRQs masked, or the interrupt master off, as selected by the PXI wait flags) it polls the PXI FIFO
// by hand.
void PMi_WaitBusy(void) {
    volatile u32 *busy = &data_0212b950;

    if (*busy == 0) {
        return;
    }
    do {
        if (((data_020dfbe4 & 2) && OS_GetProcMode() == 0x12) || ((data_020dfbe4 & 4) && OS_GetCpsrIrq() == 0x80) ||
            ((data_020dfbe4 & 8) && *(volatile u16 *)0x04000208 == 0)) {
            PXIi_HandlerRecvFifoNotEmpty();
        }
    } while (*busy != 0);
}
