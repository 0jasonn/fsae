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

// TextRenderer::onReadColorTag(ColorType) (0x020a611c): stores the colour only when the text is drawn
ARM void Knife_Message_TextRenderer_onReadColorTag(Knife::Message::TextRenderer *self, s32 color) {
    if (self->flag94 == 0 && self->flag95 == 0) {
        self->unk_b8 = color;
    }
}
