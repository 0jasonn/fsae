#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/pane.h"

// pane_c: functions Picture_getClassInfo (0x020b5944 to 0x020b5944), all matching.

// Picture_getClassInfo() (0x020b5944, provisional name): vtable slot 0 of Picture
extern "C" void *Picture_getClassInfo(void);
ARM void *Picture_getClassInfo(void) {
    return data_02126a98;
}
