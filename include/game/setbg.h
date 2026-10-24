#ifndef WIP_A_SETBG_H
#define WIP_A_SETBG_H

#include "engine/functions.h"

// Background map writers (0x0209b078 to 0x0209b6fc). Cells are u16 map entries, 32 per row.
// Declarations for the ones subtask.h does not have yet (original C++ signatures).
s32 set_bg_num_8_16(u8 *buf, s32 x, s32 y, s32 digits, u32 value, s32 size, int flag);
s32 set_bg_num_8_8(u8 *buf, s32 x, s32 y, s32 digits, u32 value, s32 size, int flag);
void set_bg_char_xywh(u8 *buf, s32 x, s32 y, s32 w, s32 h, u16 palette, u16 charSize);
void set_bg_char_8_8(u8 *buf, s32 x, s32 y, u16 palette, u16 charSize);
void set_bg_char_16_16(u8 *buf, s32 x, s32 y, u16 palette, u16 charSize);
void set_bg_NULL_xywh(u8 *buf, s32 x, s32 y, s32 w, s32 h);
void set_bg_pal_xywh(u8 *buf, s32 x, s32 y, s32 w, s32 h, u16 palette);
void set_bg_NULL_16_16(u8 *buf, s32 x, s32 y);
void set_bg_NULL_16_16_pal_chr(u8 *buf, s32 x, s32 y, u16 palette, u16 charSize);
void set_bg_char_8_16(u8 *buf, s32 x, s32 y, u16 palette, u16 charSize);

#endif
