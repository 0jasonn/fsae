#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/os/os_interrupts.h"
#include "sdk/wm/wm_system.h"

// WM_GetAID() (0x0201f2e8): the AID this device has in the current network (0 while the library has no work area).
u16 WM_GetAID(void) {
    u32 irq = OS_DisableInterrupts();
    u16 aid;

    if (data_0212b960.work != NULL) {
        aid = data_0212b960.work->aid;
    } else {
        aid = 0;
    }
    OS_RestoreInterrupts(irq);
    return aid;
}

// WM_GetConnectedAIDs() (0x0201f318): bit mask of the AIDs currently connected.
u16 WM_GetConnectedAIDs(void) {
    u32 irq = OS_DisableInterrupts();
    u32 aids;

    if (data_0212b960.work != NULL) {
        aids = data_0212b960.work->connectedAids;
    } else {
        aids = 0;
    }
    OS_RestoreInterrupts(irq);
    return aids;
}
