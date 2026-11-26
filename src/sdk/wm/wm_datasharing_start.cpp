#include "engine/functions.h"
#include "game/agent.h"
#include "sdk/wm/wm_datasharing.h"
#include "sdk/wm/wm_system.h"

// WM_StartDataSharing (0x020202d8): validates the parameters, fills the data sharing work block (the local station
// is added to aidBitmap) and installs the port callback; a parent also marks the expected stations in every data set
// and queues the first one (two in double mode).
s32 WM_StartDataSharing(void *buf, s32 port, u16 aidBitmap, u16 dataLength, s32 doubleMode) {
    WmDataSharing *sharing = (WmDataSharing *)buf;
    s32 result;
    s32 aid;
    u16 connectedAIDs = 1;
    u32 count;

    result = WMi_CheckStateEx(2, 9, 10);
    if (result != 0) {
        return result;
    }
    if (sharing == NULL) {
        return 6;
    }
    if ((u32)port >= 0x10) {
        return 6;
    }
    if (aidBitmap == 0) {
        return 6;
    }
    aid = WM_GetAID();
    if (aid == 0) {
        connectedAIDs = WM_GetConnectedAIDs();
    }
    MIi_CpuClearFast(0, sharing, 0x820);
    sharing->writeIndex = 0;
    sharing->sendIndex = 0;
    sharing->readIndex = 0;
    sharing->aidBitmap = 0;
    sharing->dataLength = dataLength;
    sharing->port = port;
    sharing->doubleMode = doubleMode ? 1 : 0;
    aidBitmap |= 1 << aid;
    sharing->aidBitmap = aidBitmap;
    count = MATH_CountPopulation(aidBitmap);
    sharing->stationCount = count;
    sharing->dataSetLength = dataLength * count;
    if (sharing->dataSetLength > 0x1fc) {
        sharing->aidBitmap = 0;
        return 6;
    }
    sharing->dataSetLength += 4;
    sharing->state = 1;
    if (aid == 0) {
        s32 res;
        int i;

        for (i = 0; i < 4; i++) {
            sharing->dataSets[i].receivedBitmap = sharing->aidBitmap & (connectedAIDs | 1);
        }
        WM_SetPortCallback(port, (u32)WmDataSharingReceiveCallback_Parent, (u32)sharing);
        for (i = 0; i < (sharing->doubleMode == 1 ? 2 : 1); i++) {
            sharing->writeIndex = (sharing->writeIndex + 1) & 3;
            res = func_02020128((void *)WmDataSharingSetDataCallback, sharing, &sharing->dataSets[i],
                                sharing->dataSetLength, sharing->aidBitmap & connectedAIDs, sharing->port, 1);
            if (res == 7) {
                sharing->sequence[i] = 0xffff;
                sharing->sendIndex = (sharing->sendIndex + 1) & 3;
            } else if (res != 0 && res != 2) {
                sharing->state = 5;
                return 1;
            }
        }
    } else {
        sharing->sendIndex = 3;
        WM_SetPortCallback(port, (u32)WmDataSharingReceiveCallback_Child, (u32)sharing);
    }
    return 0;
}
