#include "engine/functions.h"
#include "global.h"

// Functions in this file (plain names from the debug build, C linkage):
//   draw_radar_kakera (0x020a6830)

extern "C" void set_bg_char_xywh(u8 *buf, s32 x, s32 y, s32 w, s32 h, u16 palette, u16 charSize);

// draw_radar_kakera(long, void*) (0x020a6830): the kakera gauge on column 0x1b, four base blocks of height 3 and then, for
// each level from 1 to mode, a pair of blocks (height 2 and 1); the switch falls through from the highest level down
extern "C" void draw_radar_kakera(s32 mode, void *buf);
ARM void draw_radar_kakera(s32 mode, void *buf) {
    set_bg_char_xywh((u8 *)buf, 0x1b, 4, 2, 3, 0, 0x180);
    set_bg_char_xywh((u8 *)buf, 0x1b, 8, 2, 3, 0, 0x180);
    set_bg_char_xywh((u8 *)buf, 0x1b, 0xc, 2, 3, 0, 0x180);
    set_bg_char_xywh((u8 *)buf, 0x1b, 0x10, 2, 3, 0, 0x180);
    switch (mode) {
    case 0:
        break;
    case 4:
        set_bg_char_xywh((u8 *)buf, 0x1b, 0x10, 2, 2, 0, 0x12);
        set_bg_char_xywh((u8 *)buf, 0x1b, 0x12, 2, 1, 0, 0x14);
    case 3:
        set_bg_char_xywh((u8 *)buf, 0x1b, 0xc, 2, 2, 0, 0x12);
        set_bg_char_xywh((u8 *)buf, 0x1b, 0xe, 2, 1, 0, 0x14);
    case 2:
        set_bg_char_xywh((u8 *)buf, 0x1b, 8, 2, 2, 0, 0x12);
        set_bg_char_xywh((u8 *)buf, 0x1b, 0xa, 2, 1, 0, 0x14);
    case 1:
        set_bg_char_xywh((u8 *)buf, 0x1b, 4, 2, 2, 0, 0x12);
        set_bg_char_xywh((u8 *)buf, 0x1b, 6, 2, 1, 0, 0x14);
        break;
    }
}
