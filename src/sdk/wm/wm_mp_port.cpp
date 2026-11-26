#include "sdk/wm/wm_system.h"
#include "engine/functions.h"
#include "game/agent.h"
#include "sdk/os/dc_cache.h"
#include "sdk/wm/wm_datasharing.h"

// The SDK's WM_SetMPDataToPortEx (API id 0xf). Needs the WmStatusBlock fields of wip/O1/wm_system_status.h
// (0x7c mpSendBuf, 0x86, 0x182 mpReadyBitmap, 0x188 aid); the names of 0x182/0x188 are guesses.

// Checks the MP state and the data (not NULL, not the buffer being sent, 1..0x200 bytes), writes it back from the
// cache and queues it for the port; returns 2 (operating) when the command was accepted.
s32 func_02020128(void *callback, void *arg, void *sendData, u16 sendDataSize, u16 destBitmap, u16 port, u16 priority) {
    s32 result;
    BOOL mpReady = TRUE;
    WmStatusBlock *status = ((WmWork *)WMi_GetWorkPointer())->status;

    result = WMi_CheckStateEx(2, 9, 10);
    if (result != 0) {
        return result;
    }
    DC_InvalidateRange(&status->aid, 2);
    if (status->aid == 0) {
        DC_InvalidateRange(&status->mpReadyBitmap, 2);
        mpReady = status->mpReadyBitmap;
        DC_InvalidateRange(&status->unk_86, 2);
    }
    if (sendData == NULL) {
        return 6;
    }
    if (mpReady == 0) {
        return 7;
    }
    DC_InvalidateRange(&status->mpSendBuf, 2);
    if (sendData == status->mpSendBuf) {
        return 6;
    }
    if (sendDataSize > 0x200) {
        return 6;
    }
    if (sendDataSize == 0) {
        return 6;
    }
    DC_StoreRange(sendData, sendDataSize);
    result = WMi_SendCommand(0xf, 7, sendData, sendDataSize, destBitmap, port, priority, callback, arg);
    if (result == 0) {
        result = 2;
    }
    return result;
}
