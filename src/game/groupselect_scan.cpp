#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Functions in this file (names from the dsd symbols, renamed by this file's header comment):
//   groupSelect_startScanWait -> groupSelect_startScanWait

extern "C" void OS_WaitVBlankIntr(void);
extern "C" void Knife_Comm_WirelessManager_turnOn(void *manager, BOOL on);
extern "C" void Knife_Comm_WirelessManager_update(void *manager);
extern "C" void Knife_Comm_WirelessManager_startScan(void *manager, BOOL flag, const u8 *filter);

// groupSelect_startScanWait() (0x020b0f8c): switches the wireless manager on, waits until it is ready, then starts
// the scan of the group select screen
extern "C" void groupSelect_startScanWait(void);
ARM void groupSelect_startScanWait(void) {
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
