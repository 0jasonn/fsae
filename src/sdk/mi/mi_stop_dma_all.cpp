#include "sdk/mi/mi_dma.h"

// Stops all four DMA channels.
void OS_StopTimer64(void) {
    MI_StopDma(0);
    MI_StopDma(1);
    MI_StopDma(2);
    MI_StopDma(3);
}
