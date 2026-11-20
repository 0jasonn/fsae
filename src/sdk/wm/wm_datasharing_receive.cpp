#include "engine/functions.h"
#include "game/agent.h"
#include "sdk/wm/wm_datasharing.h"

// WmDataSharingReceiveCallback_Parent (0x0202096c): parent side. Received data is stored, a joining or leaving station
// changes the bitmaps of the data sets and the next data set is sent. The station bit is a local computed before the
// interrupt lock so that the constant 1 stays in a register across the call.
void WmDataSharingReceiveCallback_Parent(WmPortRecvCallback *callback) {
    WmDataSharing *sharing = callback->sharing;
    u16 aid;
    u16 index;
    u16 mask;
    u32 lock;
    u32 bit;
    u16 next;

    if (sharing == NULL) {
        return;
    }
    if (callback->errcode == 0) {
        switch (callback->state) {
        case 0x15:
            WmDataSharingStoreData(sharing, callback->aid, callback->data);
            WmDataSharingSendDataSet(sharing, 0);
            break;
        case 7:
            WmDataSharingSendDataSet(sharing, 0);
            break;
        case 9:
        case 0x1a:
            aid = callback->aid;
            bit = 1 << aid;
            lock = OS_DisableInterrupts();
            index = sharing->writeIndex;
            mask = ~bit;
            sharing->dataSets[index].receivedBitmap &= mask;
            if (sharing->doubleMode == 1) {
                next = (index + 1) & 3;
                sharing->dataSets[next].receivedBitmap &= mask;
            }
            OS_RestoreInterrupts(lock);
            WmDataSharingSendDataSet(sharing, 0);
            if (sharing->doubleMode == 1) {
                WmDataSharingSendDataSet(sharing, 0);
            }
            break;
        case 0x19:
            break;
        }
    } else {
        sharing->state = 5;
    }
}
