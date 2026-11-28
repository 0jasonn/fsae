#include "global.h"
#include "types.h"
#include "sdk/scfg/scfg.h"
#include "sdk/pxi/pxi_fifo.h"

void SCFG_Init(void) {
    PXI_SetFifoRecvCallback(0x17, func_0201aa78);
    data_02129d78[0] = 0; // busy
}
