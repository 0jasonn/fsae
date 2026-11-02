#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "knife/comm/wm_work.h"
#include "knife/comm/wm_mp_api.h"
#include "knife/comm/wirelessmanager.h"
#include "actor/object/wm_idle2parent.h"

// Knife::Comm::WirelessManager::update_idle2parent() (0x02092c0c): the idle-to-parent step, run by the timer at +0x1cd8.
// Step 1 measures the next channel, or sets the parent parameter once the channels are done; step 3 starts the parent
// (child entry callback); step 5 allocates the MP buffers and starts MP; step 7 enters the parent state (8). A failed WM call
// resets the manager.

void Knife_Comm_WirelessManager_update_idle2parent(void *self) {
    WmDWork *wm = (WmDWork *)self;
    s32 ret;

    switch (wm->timer) {
    case 1:
        Knife_Comm_WirelessManager_stepNextChannel(self);
        if (wm->channel > 0) {
            ret = Knife_Comm_WirelessManager_handleResult(
                self, WM_MeasureChannel((void *)Knife_Comm_WirelessManager_callback_WM_MeasureChannel, 0, 0, (u16)wm->channel, 0x14), 0,
                data_0211b1e8);
            if (ret != 0) {
                wm->timer = 0;
                return;
            }
            Knife_Comm_WirelessManager_internalReset(self);
            return;
        } else {
            ret = Knife_Comm_WirelessManager_handleResult(
                self, WM_SetParentParameter((void *)Knife_Comm_WirelessManager_callback_WM_StepTimer2, (u8 *)self + 0x1a0), 0,
                data_0211b1fc);
            if (ret != 0) {
                wm->timer = 2;
                return;
            }
            Knife_Comm_WirelessManager_internalReset(self);
            return;
        }
    case 3:
        ret = Knife_Comm_WirelessManager_handleResult(
            self, func_0201fb74((void *)Knife_Comm_WirelessManager_callback_WM_ChildEntry), 0, data_0211b214);
        if (ret != 0) {
            wm->timer = 4;
            return;
        }
        Knife_Comm_WirelessManager_internalReset(self);
        return;
    case 5:
        if (Knife_Comm_WirelessManager_allocMPBuffer(self) != 0) {
            ret = Knife_Comm_WirelessManager_handleResult(
                self, WM_StartMP((void *)Knife_Comm_WirelessManager_callback_WM_StartMP, wm->recvBuf, (u16)wm->recvSize, wm->sendBuf, (u16)wm->sendSize, 1),
                0, data_0211b224);
            if (ret != 0) {
                wm->timer = 6;
                return;
            }
            Knife_Comm_WirelessManager_internalReset(self);
            return;
        }
        Knife_Comm_WirelessManager_internalReset(self);
        return;
    case 7:
        wm->state = 8;
        wm->timer = 0;
        wm->unk_1cdc = 0;
        return;
    }
}
