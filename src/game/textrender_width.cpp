#include "engine/functions.h"
#include "global.h"
#include "game/decls_e.h"

// Functions in this file (plain names from the debug build, C linkage; the first argument is the TextRenderer):
//   Knife_Message_TextRenderer_calcTextWidth (0x020a54bc)

extern "C" {
u32 TextBox_FindRange(void *font, u32 ch);            // 0x020c4ee4: index of the character, 0xffff when missing
void *TextBox_FindRangeEntry(void *font, u32 index);  // 0x020c4f2c: glyph entry of the index (advance at +2)
}

// TextRenderer::calcTextWidth(Text const*) const (0x020a54bc): the width of the text in pixels, the advance of every
// character plus the spacing of the renderer (unk_98)
ARM extern "C" s32 Knife_Message_TextRenderer_calcTextWidth(const Knife::Message::TextRenderer *self,
                                                        const Knife::Message::Text *text) {
    void *app;
    Knife::Message::Text copy;
    u32 ch;
    s32 width;
    u32 index;
    u8 *glyph;

    app = KnifeApp_getField20Address(KnifeApp_getInstance());
    copy = *text;
    width = 0;
    ch = copy.readFirstCharacterAndStep(0);
    while (ch != 0) {
        index = TextBox_FindRange(app, (u16)ch);
        if (index == 0xffff) {
            index = *(u16 *)(*(u8 **)app + 2);
        }
        glyph = (u8 *)TextBox_FindRangeEntry(app, index);
        s32 step = width + (s8)glyph[2];
        width = step + self->unk_98;
        ch = copy.readFirstCharacterAndStep(0);
    }
    return width;
}
