#include "engine/functions.h"
#include "game/agent.h"
#include "sdk/wm/wm_datasharing.h"
#include "sdk/wm/wm_system.h"

// WmDataSharingSendDataSet (0x02020c54): prepares the next data set (cleared, expecting the connected stations) and sends
// the current one through the MP port. `flag` 1 drops the parent's own bit from the set that is sent.
void WmDataSharingSendDataSet(WmDataSharing *sharing, s32 flag) {
    u32 lock;

    lock = OS_DisableInterrupts();
    if (sharing->dataSets[sharing->writeIndex].receivedBitmap == 0) {
        u16 next;
        u16 index;
        u16 clearIndex;
        s32 status;
        u16 connected;

        connected = WM_GetConnectedAIDs();
        index = sharing->writeIndex;
        next = (index + 1) & 3;
        if (sharing->doubleMode == 1) {
            clearIndex = (next + 1) & 3;
        } else {
            clearIndex = next;
        }
        MIi_CpuClear16(0, &sharing->dataSets[clearIndex], 0x200);
        sharing->dataSets[clearIndex].receivedBitmap = sharing->aidBitmap & (connected | 1);
        sharing->writeIndex = next;
        sharing->dataSets[index].receivedBitmap = sharing->aidBitmap;
        if (flag == 1) {
            sharing->dataSets[index].receivedBitmap &= 0xfffe;
        }
        OS_RestoreInterrupts(lock);
        status = func_02020128((void *)WmDataSharingSetDataCallback, sharing, &sharing->dataSets[index], sharing->dataSetLength,
                                      sharing->aidBitmap & connected, sharing->port, 1);
        if (status == 7) {
            sharing->sequence[index] = 0xffff;
            sharing->sendIndex = (sharing->sendIndex + 1) & 3;
            return;
        }
        if (status != 0 && status != 2) {
            sharing->state = 5;
        }
    } else {
        OS_RestoreInterrupts(lock);
    }
}
