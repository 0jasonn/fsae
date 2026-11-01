#include "engine/functions.h"
#include "engine/menu_scroll.h"

// Menu_applyBgScroll (0x020baef4): sets the layer bits of DISPCNT from the object flag, then the scroll
// registers of BG0, BG1 and BG2 (9-bit x/y for BG0 and BG1, x 8-bit for BG2) from the object's scroll values.
void Menu_applyBgScroll(MenuScrollObj *self) {
    u32 layers = (*(u32 *)0x04000000 & 0x1f00) >> 8;
    u32 bits;
    if (self->flagLayers == 0) {
        bits = layers | 7;
    } else {
        bits = layers & ~7;
    }
    *(volatile u32 *)0x04000000 = (*(volatile u32 *)0x04000000 & ~0x1f00) | (bits << 8);
    *(u32 *)0x04000010 = ((0x200 - self->bg0X) & 0x1ff) | ((((u32)(0x200 - self->bg0Y) << 23) >> 7) & 0x1ff0000);
    *(u32 *)0x04000014 = ((0x200 - self->bg1X) & 0x1ff) | ((((u32)(0x200 - self->bg1Y) << 23) >> 7) & 0x1ff0000);
    *(u32 *)0x04000018 = ((0x100 - self->bg2X) & 0xff) | ((((u32)(0x200 - self->bg2Y) << 23) >> 7) & 0x1ff0000);
}
