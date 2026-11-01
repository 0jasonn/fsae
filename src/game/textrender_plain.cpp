#include "engine/functions.h"
#include "global.h"
#include "game/decls_e.h"

// Functions in this file (plain names from the debug build, C linkage; the first argument is the TextRenderer):
//   Knife_Message_TextRenderer_onReadPlainText (0x020a5e28)

// TextRenderer::onReadPlainText(Text const*) (0x020a5e28): when the text is only measured (flag95) the width is added to
// unk_a8, otherwise every character is drawn at unk_b0 and the position advances by its width plus the spacing
ARM extern "C" void Knife_Message_TextRenderer_onReadPlainText(Knife::Message::TextRenderer *self,
                                                           const Knife::Message::Text *text) {
    Knife::Message::Text copy;
    void *app;
    u32 ch;

    if (self->flag94 != 0) {
        return;
    }
    if (self->flag95 != 0) {
        self->unk_a8 += Knife_Message_TextRenderer_calcTextWidth(self, text);
        return;
    }
    app = KnifeApp_getField20Address(KnifeApp_getInstance());
    copy = *text;
    ch = copy.readFirstCharacterAndStep(0);
    if (ch == 0) {
        return;
    }
    do {
        u8 *slot = (u8 *)self->target + self->unk_b8;
        s32 width = func_020c5e00((u8 *)self->target + 4, app, self->unk_b0, self->unk_b4, slot[0x60], (u16)ch);
        self->unk_b0 += width + self->unk_98;
        ch = copy.readFirstCharacterAndStep(0);
    } while (ch != 0);
}
