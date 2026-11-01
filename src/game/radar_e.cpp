#include "engine/functions.h"
#include "global.h"
#include "game/radar_e_api.h"

// Functions in this file (plain names from the debug build, C linkage):
//   draw_radar_time (0x020a650c)

void set_bg_char_8_16(u8 *buf, s32 x, s32 y, u16 palette, u16 charSize);

// draw_radar_time(long, void*) (0x020a650c): the time readout on row 0x15, minutes capped at 99 then seconds, as two digit
// cells each (tile 8 + digit), with the separator tile 7 between them
void draw_radar_time(s32 time, void *buf) {
    s32 minutes;
    s32 seconds;
    u16 digit;

    minutes = time / 60;
    seconds = time % 60;
    if (minutes > 99) {
        minutes = 99;
    }
    digit = minutes / 10 + 8;
    set_bg_char_8_16((u8 *)buf, 0x1a, 0x15, 3, digit);
    digit = minutes % 10 + 8;
    set_bg_char_8_16((u8 *)buf, 0x1b, 0x15, 3, digit);
    set_bg_char_8_16((u8 *)buf, 0x1c, 0x15, 3, 7);
    digit = seconds / 10 + 8;
    set_bg_char_8_16((u8 *)buf, 0x1d, 0x15, 3, digit);
    digit = seconds % 10 + 8;
    set_bg_char_8_16((u8 *)buf, 0x1e, 0x15, 3, digit);
}

// Functions in this file (plain names from the debug build, C linkage):
//   draw_radar_power (0x020a6658), draw_radar_defense (0x020a66f0), draw_radar_speed (0x020a6788)

extern "C" void set_bg_char_xywh(u8 *buf, s32 x, s32 y, s32 w, s32 h, u16 palette, u16 charSize);
extern "C" void set_bg_NULL_16_16_pal_chr(u8 *buf, s32 x, s32 y, u16 palette, u16 charSize);
void set_bg_char_16_16(u8 *buf, s32 x, s32 y, u16 palette, u16 charSize);

// draw_radar_power(long, void*) (0x020a6658): power gauge cells (mode 1 draws the left cell only, mode 2 both)
void draw_radar_power(s32 mode, void *buf) {
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
void draw_radar_defense(s32 mode, void *buf) {
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
void draw_radar_speed(s32 mode, void *buf) {
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

// Functions in this file (plain names from the debug build, C linkage):
//   draw_radar_kakera (0x020a6830)

// draw_radar_kakera(long, void*) (0x020a6830): the kakera gauge on column 0x1b, four base blocks of height 3 and then, for
// each level from 1 to mode, a pair of blocks (height 2 and 1); the switch falls through from the highest level down
void draw_radar_kakera(s32 mode, void *buf) {
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
