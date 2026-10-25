#include "engine/functions.h"
#include "global.h"

// Functions in this file (plain names from the debug build, C linkage):
//   draw_radar_time (0x020a650c)

void set_bg_char_8_16(u8 *buf, s32 x, s32 y, u16 palette, u16 charSize);

// draw_radar_time(long, void*) (0x020a650c): the time readout on row 0x15, minutes capped at 99 then seconds, as two digit
// cells each (tile 8 + digit), with the separator tile 7 between them
extern "C" void draw_radar_time(s32 time, void *buf);
ARM void draw_radar_time(s32 time, void *buf) {
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
