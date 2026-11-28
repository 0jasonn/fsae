#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/os/dc_cache.h"
#include "sdk/os/os_arena.h"
#include "sdk/os/os_interrupts.h"
#include "sdk/os/os_message.h"
#include "sdk/pxi/pxi_fifo.h"
#include "sdk/wm/wm_system.h"
#include "engine/oam_ring.h"

// WM_Finish() (0x0201ebd8): shuts WM down (only allowed in the stop state); 3 when it was not initialised.
s32 WM_Finish(void) {
    u32 irq = OS_DisableInterrupts();
    s32 result;

    if (WMi_CheckInitialized() != 0) {
        OS_RestoreInterrupts(irq);
        return 3;
    }
    result = WMi_CheckStateEx(1, 0);
    if (result != 0) {
        return result;
    }
    WmClearFifoRecvFlag();
    PXI_SetFifoRecvCallback(10, NULL);
    data_0212b960.work = NULL;
    data_0212b960.initialized = 0;
    OS_RestoreInterrupts(irq);
    return 0;
}
