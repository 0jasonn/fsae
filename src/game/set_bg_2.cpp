#include "engine/functions.h"
#include "global.h"
#include "game/setbg.h"

extern "C" void MI_CpuFill8(void *dst, u8 value, u32 size);

// set_bg_NULL_xywh(unsigned char*, long, long, long, long) (0x0209b4c0): clears a w by h rectangle of cells.
ARM void set_bg_NULL_xywh(u8 *buf, s32 x, s32 y, s32 w, s32 h) {
    u8 *row;
    s32 i;

    row = buf + ((x + (y << 5)) << 1);
    for (i = 0; i < h; i++) {
        MI_CpuFill8(row, 0, w << 1);
        row += 0x40;
    }
}
