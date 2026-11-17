#include "engine/wm_api.h"

// Inferred SDK name. Forward the callback to the extended entry point with flag one.
s32 WM_StartParent(void *callback) {
    return WMi_StartParentEx(callback, 1);
}
