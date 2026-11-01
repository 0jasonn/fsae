#include "engine/functions.h"

// Functions in this file (plain name from the debug build, C linkage, prototype in engine/functions.h):
//   Knife_Message_TextRenderer_getBgMode (0x020a58d0)

// TextRenderer::getBgMode(bool) (0x020a58d0): the BG mode (bits 0 to 2) of DISPCNT of the main screen (nonzero flag)
// or the sub screen (zero flag). The two register reads go through volatile locals.
s32 Knife_Message_TextRenderer_getBgMode(s32 isBg) {
    volatile u32 mainCnt;
    volatile u32 subCnt;
    if (isBg) {
        mainCnt = *(volatile u32 *)0x04000000;
        return (s32)((mainCnt << 29) >> 29);
    }
    subCnt = *(volatile u32 *)0x04001000;
    return (s32)((subCnt << 29) >> 29);
}
