#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/pxi/pxi_fifo.h"
#include "sdk/tp/tp.h"

// TP_RequestAutoSamplingStopAsync() (0x0201c3e0): asks the ARM7 to stop auto sampling.
void TP_RequestAutoSamplingStopAsync(void) {
    u32 savedIrq = OS_DisableInterrupts();
    u8 sent = 0;

    if (PXI_SendWordByFifo(6, 0x3000200, 0) >= 0) {
        sent = 1;
    }
    if (sent == 0) {
        OS_RestoreInterrupts(savedIrq);
        data_0212b8e4.errorFlags |= 4;
        if (data_0212b8e4.callback != NULL) {
            data_0212b8e4.callback(2, 4, 0);
        }
        return;
    }
    data_0212b8e4.busyFlags |= 4;
    data_0212b8e4.errorFlags &= ~4;
    OS_RestoreInterrupts(savedIrq);
}

u32 TP_GetLatestIndexInAuto(void) {
    return data_0212b8e4.latestIndex;
}
