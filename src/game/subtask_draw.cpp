#include "engine/functions.h"
#include "global.h"
#include "game/subtask.h"

// Subtask draw helpers, 0x0209cd18 to 0x0209cdb0: queue a BG character write for mode 1 to 3.

// subtask_draw_ice_key (0x0209cd18)
ARM void subtask_draw_ice_key(s32 x, s32 y, u32 mode, u8 *buf) {
    switch (mode) {
    case 0:
        break;
    case 1:
        set_bg_char_8_16(buf, x, y, 4, 0x7c);
        break;
    case 2:
        set_bg_char_8_16(buf, x, y, 3, 0x7c);
        break;
    case 3:
        set_bg_char_8_16(buf, x, y, 7, 0x7c);
        break;
    }
}

// subtask_draw_fire_key (0x0209cdb0)
ARM void subtask_draw_fire_key(s32 x, s32 y, u32 mode, u8 *buf) {
    switch (mode) {
    case 0:
        break;
    case 1:
        set_bg_char_8_16(buf, x, y, 4, 0x7d);
        break;
    case 2:
        set_bg_char_8_16(buf, x, y, 3, 0x7d);
        break;
    case 3:
        set_bg_char_8_16(buf, x, y, 6, 0x7d);
        break;
    }
}
