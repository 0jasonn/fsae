#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/wirelessmgr_d.h"

// Named after the state it leaves (state 4 to state 5): counts the timer down and starts the scan (0x02092aac).
extern "C" void Knife_Comm_WirelessManager_update_waitScan(void *self);
ARM void Knife_Comm_WirelessManager_update_waitScan(void *self) {
    WirelessManagerWork *wm;

    wm = (WirelessManagerWork *)self;
    if (wm->timer == 0) {
        return;
    }
    if (wm->timer == 1) {
        wm->state = 5;
        wm->timer = 0;
        wm->unk_1cdc = 0;
    }
}
