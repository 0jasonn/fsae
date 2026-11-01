#include "global.h"
#include "types.h"
#include "knife/comm/wm_work.h"
#include "knife/comm/wirelessmanager.h"

// Knife::Comm::WirelessManager::update_parent() (0x02092e0c): the parent state step, run from update() in state 8. At timer 0
// it clears the slot table (+0x1c5c, 16 words) and the link mask, starts the data sharing step (WM_StepDataSharing) and
// records the result with handleResult. A failed result sets the timer to 1. Otherwise the link mask is copied from the
// received data and each linked slot gets the shared data address (WM_GetSharedDataAddress). At timer 1 the manager is
// reset (internalReset).

void Knife_Comm_WirelessManager_update_parent(void *self) {
    WmDWork *wm;
    s32 result;
    s32 ret;
    u16 i;

    WM_GetConnectedAIDs();
    wm = (WmDWork *)self;
    switch (wm->timer) {
    case 0:
        MI_CpuFill8((u8 *)self + 0x1c5c, 0, 0x40);
        wm->linkValue = 0;
        result = WM_StepDataSharing((u8 *)self + 0x1e0, (u8 *)self + 0xa0, (u8 *)self + 0xac0);
        ret = Knife_Comm_WirelessManager_handleResult(self, result, 0, data_0211b230);
        if (ret == 0) {
            wm->timer = 1;
            return;
        }
        if (result == 5) {
            wm->unk_1cdd = 1;
            return;
        }
        wm->linkValue = *(u16 *)((u8 *)self + 0xac2);
        for (i = 0; i < WM_FIELD(self, 0x1b0, u16) + 1; i++) {
            if (wm->linkValue & (1 << i)) {
                wm->slots[i] = (u32)WM_GetSharedDataAddress((u8 *)self + 0x1e0, (u8 *)self + 0xac0, i);
            }
        }
        return;
    case 1:
        Knife_Comm_WirelessManager_internalReset(self);
        return;
    }
}
