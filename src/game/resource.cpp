#include "engine/functions.h"
#include "global.h"

// Resource control, 0x02082c64 to 0x02082d68: ResourceCtrl runs the callback in data_02171e20[0], calls bgTrans for
// each of the four BG entries that have a flag and a pointer set, then copies the buffer that is not current
// (objAffineSet) to VRAM 0x07000000 when its flag in data_0212c50c is set.

extern u32 data_02171e20[];
#include "engine/vblank_request.h"
extern u8 data_0212c50c[];
#include "engine/display_state.h"

// ResourceCtrl (0x02082c64)
void ResourceCtrl(void) {
    void (*callback)(DISP_CTRL_ *);
    s32 other;

    callback = (void (*)(DISP_CTRL_ *))data_02171e20[0];
    if (callback != 0) {
        callback(&data_0212c6f0);
    }
    if (data_0212c6f0.bg[0].transRequest != 0 && data_0212c6f0.bg[0].buffer != 0) {
        bgTrans(&data_0212c6f0.bg[0]);
    }
    if (data_0212c6f0.bg[1].transRequest != 0 && data_0212c6f0.bg[1].buffer != 0) {
        bgTrans(&data_0212c6f0.bg[1]);
    }
    if (data_0212c6f0.bg[2].transRequest != 0 && data_0212c6f0.bg[2].buffer != 0) {
        bgTrans(&data_0212c6f0.bg[2]);
    }
    if (data_0212c6f0.bg[3].transRequest != 0 && data_0212c6f0.bg[3].buffer != 0) {
        bgTrans(&data_0212c6f0.bg[3]);
    }
    other = data_0212c4c8 ^ 1;
    if (data_0212c50c[other] == 0) {
        return;
    }
    if ((data_0212c6f0.displayFlags & 0x1000) == 0) {
        return;
    }
    MIi_CpuCopyFast(objAffineSet + (other << 10), (void *)0x7000000, 0x400);
    data_0212c50c[data_0212c4c8 ^ 1] = 0;
}
