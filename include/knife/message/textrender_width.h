#ifndef KNIFE_MESSAGE_TEXTRENDER_WIDTH_H
#define KNIFE_MESSAGE_TEXTRENDER_WIDTH_H

#include "engine/entity.h"

namespace Knife { namespace Message { class TextRenderer; class Text; } }

extern "C" {
s32 Knife_Message_TextRenderer_calcTextWidth(const Knife::Message::TextRenderer *self, const Knife::Message::Text *text);
}

#endif
