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

// WM_Init(sysWork, dmaNo) (0x0201e94c): initialises WM on a 0xf00-byte work area (32-byte aligned, in main memory).
int WM_Init(void *sysWork, u32 dmaNo) {
    s32 result = WmInitCore(sysWork, dmaNo, 0xf00);

    if (result == 0) {
        data_0212b960.work->unk_16 = 0;
    }
    return result;
}
