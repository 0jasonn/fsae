#include "sdk/wm/wm_start_parent.h"
#include "engine/functions.h"

// Inferred SDK name. Forward the callback to the extended entry point with flag one.
s32 WM_StartParent(void *callback) {
    return WMi_StartParentEx(callback, 1);
}
