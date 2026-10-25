#include "engine/functions.h"
#include "global.h"

// Functions in this file (invented name, the debug build has none):
//   Knife_Message_TextRenderer_getField50: reads a word of the renderer table at +0x50

// TextRenderer::getField50(int) (0x020a5d38): the word at +0x50 for index
extern "C" u32 Knife_Message_TextRenderer_getField50(void *a, s32 index);
ARM u32 Knife_Message_TextRenderer_getField50(void *a, s32 index) {
    return ((u32 *)((u8 *)a + 0x50))[index];
}
