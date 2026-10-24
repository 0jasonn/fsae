#include "engine/functions.h"
#include "global.h"
#include "game/subtask.h"

// Background cell writer, 0x0209b394 (set_bg_char_8_8 is 0x44 bytes; set_bg_char_16_16 is parked in between).

// set_bg_char_8_8(unsigned char*, long, long, unsigned short, unsigned short) (0x0209b394): sets the character and palette of one cell.
ARM void set_bg_char_8_8(u8 *buf, s32 x, s32 y, u16 palette, u16 charSize) {
    s32 offset = (x + (y << 5)) << 1;
    s32 mask = -0x400;

    *(u16 *)(buf + offset) = (*(u16 *)(buf + offset) & mask) | (charSize & ((u32)mask >> 22));
    *(u16 *)(buf + offset) = (*(u16 *)(buf + offset) & ~0xf000) | (((u32)palette << 28) >> 16);
}
