#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "knife/comm/wm_d.h"
#include "knife/comm/wm_mp_api.h"
#include "knife/comm/wirelessmanager.h"

// Knife::Comm::WirelessManager::update_idle2child() (0x02092fd8): the idle-to-child step, run by the timer at +0x1cd8.
// Step 1 allocates the MP buffers and starts the MP connection (WM_StartMP); a successful start moves the timer to 2,
// otherwise the manager is reset. Step 3 records the connected AIDs and the own AID in the link mask (+0x1cde), moves to
// the child state (11) and clears the timer and the controller flag.

void Knife_Comm_WirelessManager_update_idle2child(void *self) {
    WmDWork *wm;
    s32 ret;

    wm = (WmDWork *)self;
    switch (wm->timer) {
    case 0:
    case 2:
        break;
    case 1:
        if (Knife_Comm_WirelessManager_allocMPBuffer(self) != 0) {
            ret = Knife_Comm_WirelessManager_handleResult(self, WM_StartMP((void *)Knife_Comm_WirelessManager_callback_WM_StartMP, wm->recvBuf, (u16)wm->recvSize, wm->sendBuf, (u16)wm->sendSize, 1), 0, data_0211b254);
            if (ret != 0) {
                wm->timer = 2;
                return;
            }
            Knife_Comm_WirelessManager_internalReset(self);
            return;
        } else {
            Knife_Comm_WirelessManager_internalReset(self);
            return;
        }
    case 3:
        WM_FIELD(self, 0x1cde, u16) = (u16)(WM_GetConnectedAIDs() | (1 << WM_GetAID()));
        wm->state = 11;
        wm->timer = 0;
        wm->unk_1cdc = 0;
        break;
    }
}

// Knife::Comm::WirelessManager::update_child() (0x020930d8): the child state step. At timer 0 it clears the slot table (+0x1c5c)
// and the link mask, starts the data sharing step (WM_StepDataSharing) and records the result. A failed result sets the timer
// to 1; result 5 sets the flag at +0x1cdd. Otherwise the link mask is copied and each linked slot gets its shared data address;
// the first slot's link word then goes to +0x1cde. At timer 1 the manager is reset (internalReset).

void Knife_Comm_WirelessManager_update_child(void *self) {
    WmDWork *wm;
    s32 result;
    s32 ret;
    u16 i;

    wm = (WmDWork *)self;
    switch (wm->timer) {
    case 0:
        MI_CpuFill8((u8 *)self + 0x1c5c, 0, 0x40);
        wm->linkValue = 0;
        result = WM_StepDataSharing((u8 *)self + 0x1e0, (u8 *)self + 0xa0, (u8 *)self + 0xac0);
        ret = Knife_Comm_WirelessManager_handleResult(self, result, 0, data_0211b260);
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
        if (wm->slots[0] != 0) {
            WM_FIELD(self, 0x1cde, u16) = *(u16 *)wm->slots[0];
        }
        return;
    case 1:
        Knife_Comm_WirelessManager_internalReset(self);
        return;
    }
}
