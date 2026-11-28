#include "engine/functions.h"
#include "sdk/gx/gx.h"
#include "sdk/mi/mi_dma.h"


// Selects the DMA channel GX uses for its VRAM loads (-1 = CPU copy) and returns the previous channel (-1 when it was
// not one of the four hardware channels).
s32 GX_SetDefaultDMA(s32 dmaNo) {
    s32 oldDma = data_020dfb7c.defaultDma;
    u32 irq;

    if (oldDma != -1) {
        if ((u32)oldDma > 3) {
            DmaWaitFast(oldDma - 4);
        } else {
            MI_WaitDma(oldDma);
        }
    }
    irq = OS_DisableInterrupts();
    data_020dfb7c.defaultDma = dmaNo;
    OS_RestoreInterrupts(irq);
    if ((u32)oldDma > 3) {
        oldDma = -1;
    }
    return oldDma;
}
