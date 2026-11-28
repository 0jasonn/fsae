#include "engine/functions.h"
#include "sdk/gx/gx.h"

// Sets the main engine display mode, BG mode and BG0 2D/3D select; the display mode is forced to 0 while the display is off.
void GX_SetGraphicsMode(u32 dispMode, u32 bgMode, u32 bg0As3d) {
    u32 mode;
    volatile u32 *dispcnt = (volatile u32 *)0x4000000;

    mode = *dispcnt;
    data_02129824 = dispMode;
    if (data_020dfb7c.isDispOn == 0) {
        dispMode = 0;
    }
    *dispcnt = ((mode & 0xfff0fff0) | (dispMode << 16) | bgMode) | (bg0As3d << 3);
    if (data_02129824 == 0) {
        data_020dfb7c.isDispOn = 0;
    }
}
