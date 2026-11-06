#include "actor/object/multiroom.h"

// Scroll window placement. 0x02057508 ScrPosSet

extern u8 data_0212c4c8;   // buffer index (0 or 1)
extern u8 data_021348f4[]; // per-buffer "scroll changed" flags

// Centres the scroll window on (x, y): the window origin is half the screen (0x100 x 0xc0) to the upper left.
void ScrPosSet(u16 x, u16 y) {
    s16 windowX;
    s16 windowY;

    windowX = (s16)(u16)(x - 0x80);
    windowY = (s16)(u16)(y - 0x60);
    mapState.scrollX = windowX;
    mapState.scrollY = windowY;
    mapState.startX = windowX;
    mapState.startY = windowY;
    data_021348f4[data_0212c4c8] = 1;
}
