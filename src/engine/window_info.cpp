#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/pane.h"

// window_info: function Window_getClassInfo (0x020b64f0), matching. data_02126ad4 is the class info of Window.

extern u8 data_02126ad4[];

// Window_getClassInfo() (0x020b64f0, provisional name): vtable slot 0 of Window, returns the class info of Window
extern "C" void *Window_getClassInfo(void);
ARM void *Window_getClassInfo(void) {
    return data_02126ad4;
}
