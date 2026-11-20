#include "engine/functions.h"
#include "game/agent.h"
#include "sdk/wm/wm_datasharing.h"
#include "sdk/wm/wm_send_callback.h"

// WmDataSharingSetDataCallback (0x02020894): called when a data set has been sent through the data sharing port.
// It only reacts when the port still belongs to the data sharing (one of its two receive callbacks is registered) and
// the callback argument is the same work block. The parent records the sequence number of the sent data set; a
// dropped send (error 10) makes it send the data set again, any other error stops the data sharing.
void WmDataSharingSetDataCallback(void *result) {
    WmPortSendCallback *callback = (WmPortSendCallback *)result;
    u8 *work = (u8 *)WMi_GetWorkPointer();
    u8 *portEntry = work + callback->port * 4;
    void *portCallback = *(void **)(portEntry + 0xcc);
    WmDataSharing *sharing = *(WmDataSharing **)(portEntry + 0x10c);
    s32 aid;

    if (portCallback != (void *)WmDataSharingReceiveCallback_Parent && portCallback != (void *)WmDataSharingReceiveCallback_Child) {
        return;
    }
    if (sharing == NULL) {
        return;
    }
    if (sharing != callback->sharing) {
        return;
    }
    aid = WM_GetAID();
    if (callback->errcode == 0) {
        if (aid != 0) {
            return;
        }
        sharing->sequence[sharing->sendIndex] = callback->sequence >> 1;
        sharing->sendIndex = (sharing->sendIndex + 1) & 3;
    } else if (callback->errcode == 10) {
        if (aid != 0) {
            sharing->sendIndex = (sharing->sendIndex + 3) & 3;
        }
        sharing->state = 4;
    } else {
        sharing->state = 5;
    }
}
