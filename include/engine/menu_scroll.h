#ifndef WIP_F_MENU_SCROLL_H
#define WIP_F_MENU_SCROLL_H

// Scroll state of the menu background object (MenuWork.unk_358 viewed as a scroll object). Offsets from the original code.
#include "engine/functions.h"

typedef struct MenuScrollObj {
    /* 00 */ u8 unk_00[0x10];
    /* 10 */ u8 flagLayers : 1; // bit 0: clear the layer bits of DISPCNT (otherwise set them)
    /* 10 */ u8 unk_10_bits : 7;
    /* 11 */ u8 unk_11[0xa0 - 0x11];
    /* a0 */ s16 bg0X;
    /* a2 */ s16 bg0Y;
    /* a4 */ s16 bg1X;
    /* a6 */ s16 bg1Y;
    /* a8 */ s16 bg2X;
    /* aa */ s16 bg2Y;
} MenuScrollObj;

extern "C" {
void Menu_applyBgScroll(MenuScrollObj *self);
}

#endif
