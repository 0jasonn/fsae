#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/wm/wm_system.h"

// WMi_SetCallbackTable(id, callback) (0x0201ec48): installs the callback for one WM command.
void WMi_SetCallbackTable(u32 id, WmCallback callback) {
    data_0212b960.work->callbackTable[id] = callback;
}
