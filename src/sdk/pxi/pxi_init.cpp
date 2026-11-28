#include "global.h"
#include "types.h"
#include "sdk/pxi/pxi_fifo.h"
#include "sdk/os/os_irq.h"

// PXI_Init: clears the callback table, enables the FIFO receive interrupt and handshakes with the ARM7 through the
// IPC sync register (0x04000180) until both sides report the same state.
void PXI_Init(void) {
    u32 irq;
    s32 i;
    s32 count;
    s32 timeout;
    u32 data;
    volatile u16 *syncReg;
    PxiSharedWork *work;

    irq = OS_DisableInterrupts();
    if (data_02129ccc == 0) {
        data_02129ccc = 1;
        work = PXI_SHARED_WORK;
        work->callbackMask[0] = 0;
        for (i = 0; i < 32; i++) {
            data_02129cd0[i] = NULL;
        }
        *(volatile u16 *)0x04000184 = 0xc408;
        OS_ResetRequestIrqMask(0x40000);
        OS_SetIrqFunction(0x40000, PXIi_HandlerRecvFifoNotEmpty);
        OS_EnableIrqMask(0x40000);
        syncReg = (volatile u16 *)0x04000180;
        count = 0;
        for (;;) {
            data = *syncReg & 0xf;
            *syncReg = (u16)(data << 8);
            if (data == 0 && count > 4) {
                break;
            }
            timeout = 1000;
            if ((*syncReg & 0xf) == data) {
                for (;;) {
                    if (timeout <= 0) {
                        count = 0;
                        break;
                    }
                    timeout--;
                    if ((*syncReg & 0xf) != data) {
                        break;
                    }
                }
            }
            count++;
        }
    }
    OS_RestoreInterrupts(irq);
}
