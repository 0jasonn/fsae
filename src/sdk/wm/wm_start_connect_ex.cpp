#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/os/dc_cache.h"
#include "sdk/wm/wm_system.h"
#include "sdk/wm/wm_standard.h"

// WM_StartConnectEx(callback, bssDesc, ssid, powerSave, authMode) (0x0201fd70): connects to the parent described by
// bssDesc (its first halfword is its length in halfwords) and sends WM_StartConnectEx (command 0xc) directly. A NULL
// ssid sends zeros.
s32 WM_StartConnectEx(void *callback, u16 *bssDesc, const u8 *ssid, u32 powerSave, u16 authMode) {
    WmStartConnectExReq request;
    WmWork *work;
    s32 result = WMi_CheckStateEx(1, 2);

    if (result != 0) {
        return result;
    }
    if (WMi_CheckEnableFlag() == 0) {
        return 4;
    }
    if (bssDesc == NULL) {
        return 6;
    }
    DC_StoreRange(bssDesc, bssDesc[0] * 2);
    work = (WmWork *)WMi_GetWorkPointer();
    work->aid = 0;
    work->connectedAids = 0;
    WMi_SetCallbackTable(0xc, (WmCallback)callback);
    request.apiId = 0xc;
    request.bssDesc = bssDesc;
    if (ssid != NULL) {
        MI_CpuCopy8(ssid, request.ssid, 0x18);
    } else {
        MI_CpuFill8(request.ssid, 0, 0x18);
    }
    request.powerSave = powerSave;
    request.authMode = authMode;
    result = WMi_SendCommandDirect((u16 *)&request, 0x28);
    if (result == 0) {
        result = 2;
    }
    return result;
}
