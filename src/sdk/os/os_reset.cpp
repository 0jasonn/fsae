#include "global.h"
#include "types.h"
#include "sdk/os/os_reset.h"
#include "sdk/os/os_kind_terminate_api.h"
#include "sdk/pxi/pxi_fifo.h"

void OS_InitReset(void) {
    if (data_02129c90 != 0) {
        return;
    }
    data_02129c90 = 1;
    Engine_Relay0201a070();
    while (!PXI_IsCallbackReady(12, 1)) {
    }
    PXI_SetFifoRecvCallback(12, (PxiFifoCallbackFn)Os_TerminateByKind);
}
