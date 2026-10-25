#include "engine/functions.h"
#include "global.h"

// Functions in this file (invented name, the debug build has none):
//   Knife_Message_TextRenderer_returnZero: returns 0 (a default handler of the text renderer)

// TextRenderer::returnZero() (0x020a58ac): a default that returns 0
extern "C" s32 Knife_Message_TextRenderer_returnZero(void *a);
ARM s32 Knife_Message_TextRenderer_returnZero(void *a) {
    return 0;
}
