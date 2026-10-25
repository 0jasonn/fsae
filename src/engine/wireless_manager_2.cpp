#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/wireless_manager_d.h"

// Knife::Comm::WirelessManager, 0x02090ecc. func_02090ecc (C++ linkage as declared in functions.h): the flag at 0x1cdc.
// The unit starts here because getState (0x02090ea4) is parked in scratch/agentD/nonmatching.

ARM s32 func_02090ecc(void *manager) {
    WirelessManagerWork *wm;

    wm = (WirelessManagerWork *)manager;
    return wm->unk_1cdc;
}
