#include "engine/functions.h"
#include "global.h"

// Functions in this file (plain names from the debug build, C linkage):
//   draw_radar_power (0x020a6658), draw_radar_defense (0x020a66f0), draw_radar_speed (0x020a6788)

extern "C" void set_bg_char_xywh(u8 *buf, s32 x, s32 y, s32 w, s32 h, u16 palette, u16 charSize);
extern "C" void set_bg_NULL_16_16_pal_chr(u8 *buf, s32 x, s32 y, u16 palette, u16 charSize);
void set_bg_char_16_16(u8 *buf, s32 x, s32 y, u16 palette, u16 charSize);

// draw_radar_power(long, void*) (0x020a6658): power gauge cells (mode 1 draws the left cell only, mode 2 both)
extern "C" void draw_radar_power(s32 mode, void *buf);
ARM void draw_radar_power(s32 mode, void *buf) {
    set_bg_NULL_16_16_pal_chr((u8 *)buf, 2, 6, 0, 0x180);
    set_bg_NULL_16_16_pal_chr((u8 *)buf, 4, 6, 0, 0x180);
    if (mode != 1) {
        if (mode != 2) {
            return;
        }
        set_bg_char_16_16((u8 *)buf, 4, 6, 0, 1);
    }
    set_bg_char_16_16((u8 *)buf, 2, 6, 0, 1);
}

// draw_radar_defense(long, void*) (0x020a66f0): defense gauge cells, same shape as the power gauge on row 11
extern "C" void draw_radar_defense(s32 mode, void *buf);
ARM void draw_radar_defense(s32 mode, void *buf) {
    set_bg_NULL_16_16_pal_chr((u8 *)buf, 2, 0xb, 0, 0x180);
    set_bg_NULL_16_16_pal_chr((u8 *)buf, 4, 0xb, 0, 0x180);
    if (mode != 1) {
        if (mode != 2) {
            return;
        }
        set_bg_char_16_16((u8 *)buf, 4, 0xb, 1, 3);
    }
    set_bg_char_16_16((u8 *)buf, 2, 0xb, 1, 3);
}

// draw_radar_speed(long, void*) (0x020a6788): speed gauge cells on row 16
extern "C" void draw_radar_speed(s32 mode, void *buf);
ARM void draw_radar_speed(s32 mode, void *buf) {
    set_bg_NULL_16_16_pal_chr((u8 *)buf, 2, 0x10, 0, 0x180);
    set_bg_NULL_16_16_pal_chr((u8 *)buf, 4, 0x10, 0, 0x180);
    if (mode != 1) {
        if (mode != 2) {
            return;
        }
        set_bg_char_16_16((u8 *)buf, 4, 0x10, 2, 5);
    }
    set_bg_char_16_16((u8 *)buf, 2, 0x10, 2, 5);
}
