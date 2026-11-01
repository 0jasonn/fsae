#include "engine/functions.h"
#include "global.h"
#include "game/decls_e.h"

// Functions in this file (plain names from the debug build, C linkage; the first argument is the TextRenderer):
//   Knife_Message_TextRenderer_getScreenAddress (0x020a590c)

// TextRenderer::getScreenAddress(bool, int, int, int, int) const (0x020a590c): the address of the cell (x, y) of the
// screen buffer of the layer, a 16-bit cell for the table values 0 and 2 and a byte for 1; NULL for other values
extern "C" void *Knife_Message_TextRenderer_getScreenAddress(const Knife::Message::TextRenderer *self, s32 isBg,
                                                             s32 index, s32 bgMode, s32 x, s32 y) {
    s32 table;
    u8 *screen;
    s32 width;

    table = Knife_Message_TextRenderer_getTableValue(index, bgMode);
    screen = (u8 *)func_020a59ac((Knife::Message::TextRenderer *)self, isBg, index);
    width = Knife_Message_TextRenderer_getScreenWidth(isBg, index);
    switch (table) {
    case 0:
        return screen + (width * y + x) * 2;
    case 1:
        return screen + (width * y + x);
    case 2:
        return screen + (width * y + x) * 2;
    }
    return NULL;
}
