#include "sdk/wm/wm_api.h"

// Inferred SDK name. The standard enable entry uses mode zero.
s32 WM_Enable(void *callback) {
    return WMi_EnableEx(callback, 0);
}
