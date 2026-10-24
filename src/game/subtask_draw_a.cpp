#include "engine/functions.h"
#include "global.h"
#include "game/subtask.h"
#include "game/setbg.h"

// Subtask draw helpers, 0x0209ca38 to 0x0209cd18 (subtask_draw_ice_key is in subtask_draw.cpp).
// Each one writes the background cells of one item icon for the given mode.

// subtask_draw_total_ruppy (0x0209ca38): number of ruppies, then the rupee icon to its right.
ARM void subtask_draw_total_ruppy(s32 x, s32 y, u32 mode, u8 *buf) {
    s32 width = set_bg_num_8_16(buf, x, y, 4, mode, 8, 1);

    set_bg_NULL_16_16(buf, x - 2, y);
    set_bg_char_16_16(buf, x + 6 - width, y, 5, 0x7e);
}

// subtask_draw_medal (0x0209cab0)
ARM void subtask_draw_medal(s32 x, s32 y, u32 mode, u8 *buf) {
    set_bg_num_8_8(buf, x, y, 1, mode, 3, 0);
}

// subtask_draw_daikaitengiri (0x0209caf0)
ARM void subtask_draw_daikaitengiri(s32 x, s32 y, u32 mode, u8 *buf) {
    if (mode == 0) {
        set_bg_NULL_16_16(buf, x, y);
    } else {
        set_bg_char_16_16(buf, x, y, 1, 0x6e);
    }
}

// subtask_draw_mastersword (0x0209cb40)
ARM void subtask_draw_mastersword(s32 x, s32 y, u32 mode, u8 *buf) {
    if (mode == 0) {
        set_bg_NULL_16_16(buf, x, y);
    } else {
        set_bg_char_16_16(buf, x, y, 1, 0x70);
    }
}

// subtask_draw_kazenosinden (0x0209cb90)
ARM void subtask_draw_kazenosinden(s32 x, s32 y, u32 mode, u8 *buf) {
    if (mode == 0) {
        set_bg_NULL_16_16(buf, x, y);
    } else {
        set_bg_char_16_16(buf, x, y, 3, 0x72);
    }
}

// subtask_draw_tokinoshinden (0x0209cbe0)
ARM void subtask_draw_tokinoshinden(s32 x, s32 y, u32 mode, u8 *buf) {
    if (mode == 0) {
        set_bg_NULL_16_16(buf, x, y);
    } else {
        set_bg_char_16_16(buf, x, y, 3, 0x74);
    }
}

// subtask_draw_shuurenjo (0x0209cc30)
ARM void subtask_draw_shuurenjo(s32 x, s32 y, u32 mode, u8 *buf) {
    if (mode == 0) {
        set_bg_NULL_16_16(buf, x, y);
    } else {
        set_bg_char_16_16(buf, x, y, 4, 0x76);
    }
}

// subtask_draw_mori_key (0x0209cc80): the key icon, palette depends on the mode (1 to 3).
ARM void subtask_draw_mori_key(s32 x, s32 y, u32 mode, u8 *buf) {
    switch (mode) {
    case 0:
        break;
    case 1:
        set_bg_char_8_16(buf, x, y, 4, 0x7b);
        break;
    case 2:
        set_bg_char_8_16(buf, x, y, 3, 0x7b);
        break;
    case 3:
        set_bg_char_8_16(buf, x, y, 5, 0x7b);
        break;
    }
}
