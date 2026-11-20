#include "sdk/wm/wm_work.h"

extern void *data_0212b960[];

// Provisional name. Return the wireless system work pointer.
void *WMi_GetWorkPointer(void) {
    return data_0212b960[1];
}
