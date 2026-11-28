#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/os/dc_cache.h"
#include "sdk/wm/wm_system.h"
#include "sdk/wm/wm_validate_parent.h"
#include "sdk/wm/wm_standard.h"

// WM_SetParentParameter(callback, parentParam) (0x0201f9c0): validates the parent settings (sizes, key sharing overhead)
// and sends WM_SetParentParameter (command 7). Returns 6 for bad parameters.
s32 WM_SetParentParameter(void *callback, void *parentParam) {
    WmParentParam *param = (WmParentParam *)parentParam;
    s32 result = WMi_CheckStateEx(1, 2);
    u32 keySharing;

    if (result != 0) {
        return result;
    }
    if (WMi_CheckEnableFlag() == 0) {
        return 4;
    }
    if (param == NULL) {
        return 6;
    }
    if (param->userGameInfoLength != 0 && param->userGameInfo == NULL) {
        return 6;
    }
    keySharing = param->ksFlag;
    if (param->parentMaxSize + (keySharing != 0 ? 0x2a : 0) > 0x200 ||
        param->childMaxSize + (keySharing != 0 ? 6 : 0) > 0x200) {
        return 6;
    }
    WMi_ValidateParentParameter(param);
    WMi_SetCallbackTable(7, (WmCallback)callback);
    DC_StoreRange(param, 0x40);
    if (param->userGameInfoLength != 0) {
        DC_StoreRange(param->userGameInfo, param->userGameInfoLength);
    }
    result = WMi_SendCommand(7, 1, param);
    if (result == 0) {
        result = 2;
    }
    return result;
}
