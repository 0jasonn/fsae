#include "engine/functions.h"
#include "global.h"

// Functions in this file (invented name, the debug build has none):
//   Knife_Message_TextRenderer_getTableValue: reads a word from the 16-byte rows of data_020de6fc

extern u8 data_020de6fc[]; // table of 16-byte rows

// TextRenderer::getTableValue(int, int) (0x020a5a44): word number index of row
extern "C" u32 Knife_Message_TextRenderer_getTableValue(s32 index, s32 row);
ARM u32 Knife_Message_TextRenderer_getTableValue(s32 index, s32 row) {
    return ((u32 *)(data_020de6fc + (row << 4)))[index];
}
