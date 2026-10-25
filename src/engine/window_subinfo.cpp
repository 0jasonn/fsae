#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/pane.h"

// window_subinfo: function Window_getSubClassInfo (0x020b7074), matching.

extern u8 data_02126b1c[];

extern "C" void *Window_getSubClassInfo(void);
ARM void *Window_getSubClassInfo(void) {
    return data_02126b1c;
}
