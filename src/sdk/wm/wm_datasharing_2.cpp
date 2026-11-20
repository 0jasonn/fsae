#include "engine/functions.h"
#include "game/agent.h"
#include "sdk/wm/wm_datasharing.h"

// WmDataSharingReceiveCallback_Child (0x02020aa0): child side. Received data of the parent is stored in the next data
// set (limited to 0x200 bytes), together with its sequence number.
void WmDataSharingReceiveCallback_Child(WmPortRecvCallback *callback) {
    WmDataSharing *sharing = callback->sharing;
    u16 length;
    u16 bitmap;
    u16 *data;
    s32 aid;

    if (sharing == NULL) {
        return;
    }
    if (callback->errcode == 0) {
        switch (callback->state) {
        case 7:
        case 9:
        case 0x19:
        case 0x1a:
            break;
        case 0x15:
            data = callback->data;
            length = callback->length;
            bitmap = data[0];
            aid = WM_GetAID();
            if (length != sharing->dataSetLength) {
                if (length > 0x200) {
                    length = 0x200;
                }
            }
            if (length < 4) {
                return;
            }
            if ((bitmap & (1 << aid)) == 0) {
                return;
            }
            MIi_CpuCopy16(data, &sharing->dataSets[sharing->writeIndex], length);
            sharing->sequence[sharing->writeIndex] = callback->sequence >> 1;
            sharing->writeIndex = (sharing->writeIndex + 1) & 3;
            break;
        }
    } else {
        sharing->state = 5;
    }
}

// WmDataSharingStoreData (0x02020b84, called WmDataSharingStoreData): stores the data one station sent (NULL clears the slot) in
// its place of the current data set; when the current set already has that station's data the next set is used (double
// mode). The station is then marked as received and as sent.
void WmDataSharingStoreData(WmDataSharing *sharing, u16 aid, u16 *data) {
    u16 bit = 1 << aid;
    u16 index;
    u16 *target;
    u32 lock;

    if ((sharing->aidBitmap & bit) == 0) {
        return;
    }
    index = sharing->writeIndex;
    if ((sharing->dataSets[index].receivedBitmap & bit) == 0) {
        if (sharing->doubleMode != 1) {
            return;
        }
        index = (index + 1) & 3;
        if ((sharing->dataSets[index].receivedBitmap & bit) == 0) {
            return;
        }
    }
    target = (u16 *)WmGetSharedDataAddress(sharing, sharing->aidBitmap, sharing->dataSets[index].data, aid);
    if (data != NULL) {
        MIi_CpuCopy16(data, target, sharing->dataLength);
    } else {
        MIi_CpuClear16(0, target, sharing->dataLength);
    }
    lock = OS_DisableInterrupts();
    sharing->dataSets[index].receivedBitmap &= ~bit;
    sharing->dataSets[index].sentBitmap |= bit;
    OS_RestoreInterrupts(lock);
}
