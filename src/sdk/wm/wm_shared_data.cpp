#include "engine/functions.h"
#include "knife/comm/wirelessmanager.h"
#include "sdk/wm/wm_datasharing.h"
#include "game/agent.h"

// WM_GetSharedDataAddress (0x02020da4): address of the data of station `aid` inside a data set, or NULL when the set is
// missing or the station has not both sent and received its data yet.
void *WM_GetSharedDataAddress(void *sharingBlock, void *dataSetBlock, u16 aid) {
    WmDataSharing *sharing = (WmDataSharing *)sharingBlock;
    WmDataSet *dataSet = (WmDataSet *)dataSetBlock;
    u16 received;
    u16 sent;
    u32 aidBit = 1 << aid;

    if (sharing == NULL) {
        return NULL;
    }
    if (dataSet == NULL) {
        return NULL;
    }
    received = dataSet->receivedBitmap;
    sent = dataSet->sentBitmap;
    if ((received & aidBit) == 0) {
        return NULL;
    }
    if ((sent & aidBit) == 0) {
        return NULL;
    }
    return WmGetSharedDataAddress(sharing, received, dataSet->data, aid);
}
