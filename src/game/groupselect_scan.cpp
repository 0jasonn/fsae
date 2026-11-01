#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/wirelessmgr_update_api.h"
#include "game/groupselect_scan_api.h"

// Functions in this file (names from the dsd symbols, renamed by this file's header comment):
//   groupSelect_startScanWait -> groupSelect_startScanWait

extern "C" void OS_WaitVBlankIntr(void);

// groupSelect_startScanWait() (0x020b0f8c): switches the wireless manager on, waits until it is ready, then starts
// the scan of the group select screen
void groupSelect_startScanWait(void) {
    void *manager;
    s32 state;

    manager = func_020909c8();
    state = Knife_Comm_WirelessManager_getState(manager);
    if (state == 0) {
        Knife_Comm_WirelessManager_turnOn(manager, 0);
        if (state != 2) {
            do {
                OS_WaitVBlankIntr();
                Knife_Comm_WirelessManager_update(manager);
            } while (Knife_Comm_WirelessManager_getState(manager) != 2);
        }
    }
    Knife_Comm_WirelessManager_startScan(manager, 1, NULL);
}
