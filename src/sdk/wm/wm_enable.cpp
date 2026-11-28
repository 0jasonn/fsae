#include "sdk/wm/wm_enable.h"
#include "engine/functions.h"
#include "sdk/wm/wm_standard.h"

// Inferred SDK name. The standard enable entry uses mode zero.
s32 WM_Enable(void *callback) {
    return WMi_EnableEx(callback, 0);
}
