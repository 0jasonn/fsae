#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/wirelessmgr_d.h"

// Knife::Comm::WirelessManager::update() (0x02090c88): runs with interrupts disabled. Dispatches on the state index
// (0 to 15) to the state functions, then decrements the TTL of the 16 parent entries while connected.

extern "C" void Knife_Comm_WirelessManager_update(void *self);
ARM void Knife_Comm_WirelessManager_update(void *self) {
    WmInterruptSection section;
    WirelessManagerWork *wm;
    s32 i;

    wm = (WirelessManagerWork *)self;
    if (wm->allocator == NULL) {
        return;
    }
    if (wm->timer == -999) {
        Knife_Comm_WirelessManager_internalReset(self);
    }
    if (wm->timer == -1000) {
        wm->state = 15;
        wm->timer = 0;
    }
    wm->unk_1cdd = 0;
    switch (wm->state) {
    case 0: Knife_Comm_WirelessManager_update_empty0(self); break;
    case 1: Knife_Comm_WirelessManager_update_off2idle(self); break;
    case 2: Knife_Comm_WirelessManager_update_idle(self); break;
    case 3: Knife_Comm_WirelessManager_update_idle2off(self); break;
    case 4: Knife_Comm_WirelessManager_update_waitScan(self); break;
    case 5: Knife_Comm_WirelessManager_update_scan(self); break;
    case 6: Knife_Comm_WirelessManager_update_scan2idle(self); break;
    case 7: Knife_Comm_WirelessManager_update_idle2parent(self); break;
    case 8: Knife_Comm_WirelessManager_update_parent(self); break;
    case 9: Knife_Comm_WirelessManager_update_parent2idle(self); break;
    case 10: Knife_Comm_WirelessManager_update_idle2child(self); break;
    case 11: Knife_Comm_WirelessManager_update_child(self); break;
    case 12: Knife_Comm_WirelessManager_update_child2idle(self); break;
    case 13: Knife_Comm_WirelessManager_update_reset(self); break;
    case 14: Knife_Comm_WirelessManager_update_empty14(self); break;
    case 15: Knife_Comm_WirelessManager_update_empty15(self); break;
    }
    if (wm->state >= 2) {
        for (i = 0; i < 16; i++) {
            ((Knife::Comm::ParentInfo *)((u8 *)self + 0xd04 + i * 0xd0))->decrementTTL();
        }
    }
}
