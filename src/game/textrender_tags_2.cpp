#include "engine/functions.h"
#include "global.h"
#include "game/message_e.h"

// Functions in this file (plain names from the debug build, C linkage; the first argument is the TextRenderer):
//   Knife_Message_TextRenderer_onReadNewLine (0x020a5f14)
//   Knife_Message_TextRenderer_onReadPictTag (0x020a5fd4)
//   Knife_Message_TextRenderer_onReadButtonTag (0x020a602c)
//   Knife_Message_TextRenderer_onReadBlankTag (0x020a6084)
//   Knife_Message_TextRenderer_onReadCenterTag (0x020a60b4)
//   Knife_Message_TextRenderer_onReadRightTag (0x020a60e8)
//   Knife_Message_TextRenderer_onReadColorTag (0x020a611c)

extern "C" s32 Knife_Message_TextRenderer_renderPictogram(Knife::Message::TextRenderer *self, s32 pictogramId);
extern "C" void Knife_Message_TextRenderer_onReadPictTag(Knife::Message::TextRenderer *self, s32 pictogram);
extern "C" void Knife_Message_TextRenderer_onReadButtonTag(Knife::Message::TextRenderer *self, s32 button);
extern "C" void Knife_Message_TextRenderer_onReadBlankTag(Knife::Message::TextRenderer *self, s32 width);
extern "C" void Knife_Message_TextRenderer_onReadCenterTag(Knife::Message::TextRenderer *self);
extern "C" void Knife_Message_TextRenderer_onReadRightTag(Knife::Message::TextRenderer *self);
extern "C" void Knife_Message_TextRenderer_onReadColorTag(Knife::Message::TextRenderer *self, s32 color);
extern "C" void Knife_Message_TextRenderer_onReadNewLine(Knife::Message::TextRenderer *self);
extern "C" void *KnifeApp_getField20Address(void *app);

// TextRenderer::onReadPictTag(Pictogram) (0x020a5fd4): a picture while the text is measured adds its width, otherwise it
// is drawn and its width is added to the line
ARM void Knife_Message_TextRenderer_onReadPictTag(Knife::Message::TextRenderer *self, s32 pictogram) {
    if (self->flag94 != 0) {
        return;
    }
    if (self->flag95 != 0) {
        s32 advance = self->unk_98 + 0x10;
        self->unk_a8 = self->unk_a8 + advance;
        return;
    }
    Knife_Message_TextRenderer_renderPictogram(self, pictogram - 1);
    {
        s32 advance = self->unk_98 + 0x10;
        self->unk_b0 = self->unk_b0 + advance;
    }
}

// TextRenderer::onReadButtonTag(Button) (0x020a602c): as onReadPictTag, with the button's picture index
ARM void Knife_Message_TextRenderer_onReadButtonTag(Knife::Message::TextRenderer *self, s32 button) {
    if (self->flag94 != 0) {
        return;
    }
    if (self->flag95 != 0) {
        s32 advance = self->unk_98 + 0x10;
        self->unk_a8 = self->unk_a8 + advance;
        return;
    }
    Knife_Message_TextRenderer_renderPictogram(self, button + 0x1b);
    {
        s32 advance = self->unk_98 + 0x10;
        self->unk_b0 = self->unk_b0 + advance;
    }
}

// TextRenderer::onReadBlankTag(int) (0x020a6084): adds a blank of the given width to the measured or line position
ARM void Knife_Message_TextRenderer_onReadBlankTag(Knife::Message::TextRenderer *self, s32 width) {
    if (self->flag94 != 0) {
        return;
    }
    if (self->flag95 != 0) {
        self->unk_a8 = self->unk_a8 + width;
    } else {
        self->unk_b0 = self->unk_b0 + width;
    }
}

// TextRenderer::onReadCenterTag() (0x020a60b4): centres the current line: half of the target width minus the line width
ARM void Knife_Message_TextRenderer_onReadCenterTag(Knife::Message::TextRenderer *self) {
    if (self->flag94 != 0 || self->flag95 != 0) {
        return;
    }
    self->unk_b0 = (self->target->unk_38 * 8 - self->unk_a8) / 2;
}

// TextRenderer::onReadRightTag() (0x020a60e8): aligns the current line to the right edge of the target
ARM void Knife_Message_TextRenderer_onReadRightTag(Knife::Message::TextRenderer *self) {
    if (self->flag94 == 0 && self->flag95 == 0) {
        self->unk_b0 = self->target->unk_38 * 8 - self->unk_a8;
    }
}

