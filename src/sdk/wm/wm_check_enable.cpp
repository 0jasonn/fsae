#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/wm/wm_system.h"

// WMi_CheckEnableFlag() (0x0201f39c): 1 when the two platform queries (0x02019968 and 0x02019974) report that WM may be
// enabled, else 0.
s32 WMi_CheckEnableFlag(void) {
    if (func_02019968() == 1 && func_02019974() == 0) {
        return 1;
    }
    return 0;
}
