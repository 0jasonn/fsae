#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "ui/widget/pane.h"
#include "ui/widget/window_subinfo_api.h"

// window_subinfo: function Window_getSubClassInfo (0x020b7074), matching.

extern u8 data_02126b1c[];

void *Window_getSubClassInfo(void) {
    return data_02126b1c;
}
