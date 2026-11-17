#include "engine/functions.h"
#include "global.h"
#include "knife/subtask/subtask.h"
#include "game/setbg.h"

// Subtask draw helpers, 0x0209ca38 to 0x0209cd18 (subtask_draw_ice_key is in subtask_draw.cpp).
// Each one writes the background cells of one item icon for the given mode.

// subtask_draw_total_ruppy (0x0209ca38): number of ruppies, then the rupee icon to its right.
void subtask_draw_total_ruppy(s32 x, s32 y, u32 mode, u8 *buf) {
    s32 width = set_bg_num_8_16(buf, x, y, 4, mode, 8, 1);

    set_bg_NULL_16_16(buf, x - 2, y);
    set_bg_char_16_16(buf, x + 6 - width, y, 5, 0x7e);
}

// subtask_draw_medal (0x0209cab0)
void subtask_draw_medal(s32 x, s32 y, u32 mode, u8 *buf) {
    set_bg_num_8_8(buf, x, y, 1, mode, 3, 0);
}

// subtask_draw_daikaitengiri (0x0209caf0)
void subtask_draw_daikaitengiri(s32 x, s32 y, u32 mode, u8 *buf) {
    if (mode == 0) {
        set_bg_NULL_16_16(buf, x, y);
    } else {
        set_bg_char_16_16(buf, x, y, 1, 0x6e);
    }
}

// subtask_draw_mastersword (0x0209cb40)
void subtask_draw_mastersword(s32 x, s32 y, u32 mode, u8 *buf) {
    if (mode == 0) {
        set_bg_NULL_16_16(buf, x, y);
    } else {
        set_bg_char_16_16(buf, x, y, 1, 0x70);
    }
}

// subtask_draw_kazenosinden (0x0209cb90)
void subtask_draw_kazenosinden(s32 x, s32 y, u32 mode, u8 *buf) {
    if (mode == 0) {
        set_bg_NULL_16_16(buf, x, y);
    } else {
        set_bg_char_16_16(buf, x, y, 3, 0x72);
    }
}

// subtask_draw_tokinoshinden (0x0209cbe0)
void subtask_draw_tokinoshinden(s32 x, s32 y, u32 mode, u8 *buf) {
    if (mode == 0) {
        set_bg_NULL_16_16(buf, x, y);
    } else {
        set_bg_char_16_16(buf, x, y, 3, 0x74);
    }
}

// subtask_draw_shuurenjo (0x0209cc30)
void subtask_draw_shuurenjo(s32 x, s32 y, u32 mode, u8 *buf) {
    if (mode == 0) {
        set_bg_NULL_16_16(buf, x, y);
    } else {
        set_bg_char_16_16(buf, x, y, 4, 0x76);
    }
}

// subtask_draw_mori_key (0x0209cc80): the key icon, palette depends on the mode (1 to 3).
void subtask_draw_mori_key(s32 x, s32 y, u32 mode, u8 *buf) {
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

// Subtask draw helpers, 0x0209cd18 to 0x0209cdb0: queue a BG character write for mode 1 to 3.

// subtask_draw_ice_key (0x0209cd18)
void subtask_draw_ice_key(s32 x, s32 y, u32 mode, u8 *buf) {
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
void subtask_draw_fire_key(s32 x, s32 y, u32 mode, u8 *buf) {
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

extern u8 data_0217d1b4[];

// Write attr0 and attr1 together, followed by the tile, priority and palette in attr2.
BOOL subtask_draw_oam(s32 x, s32 y, s32 charNo, s32 palette, GXOamShape shape, GXOamAttr *attr) {
    u8 *out = (u8 *)attr;
    *(u32 *)out = (u32)shape | ((u32)y & 0xff) | (((u32)x << 23) >> 7);
    *(u16 *)(out + 4) = (u16)(charNo | 0x400 | ((u32)palette << 12));
    return TRUE;
}

BOOL subtask_draw_oam_eff(s32 x, s32 y, s32 charNo, s32 palette, GXOamShape shape, GXOamAttr *attr, GXOamEffect effect) {
    u8 *out = (u8 *)attr;
    *(u32 *)out = (u32)shape | ((u32)y & 0xff) | (((u32)x << 23) >> 7) | (u32)effect;
    *(u16 *)(out + 4) = (u16)(charNo | 0x400 | ((u32)palette << 12));
    return TRUE;
}

// subtask_draw_oam_you (0x0209ceb8)
BOOL subtask_draw_oam_you(s32 x, s32 y, s32 palette, GXOamAttr *attr) {
    return subtask_draw_oam(x, y, 0x140, palette, (GXOamShape)0x80004000, attr);
}

// subtask_draw_oam_link (0x0209cee4)
s32 subtask_draw_oam_link(s32 x, s32 y, NNSG2dCellAnimation *anim, GXOamAttr *attr, s32 c) {
    s32 i;
    s32 pos[2];
    s32 count;

    pos[0] = x;
    pos[1] = y;
    count = func_020c40a4(attr, 4, anim->cellRef, 0, pos, 0, 0);
    ResPlayer_AdvanceAndRefresh(anim, c);
    for (i = 0; i < count; i++) {
        attr[i].attr2 = (attr[i].attr2 & ~0xc00) | 0x400;
    }
    return count;
}

// subtask_redraw_text (0x0209cf68): Knife_Message_RedrawText with no argument list.
void subtask_redraw_text(s32 index) {
    Knife_Message_RedrawText(index, 0);
}

// subtask_setFlag (0x0209cf78): stores a byte in the subtask flag table.
void subtask_setFlag(u32 index, u8 value) {
    data_0217d1b4[index] = value;
}

// subtask_getFlag (0x0209cf88): reads a signed byte from the subtask flag table.
s8 subtask_getFlag(u32 index) {
    return (s8)data_0217d1b4[index];
}
