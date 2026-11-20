#ifndef KNIFE_MESSAGE_TEXTRENDER_SCREENADDR_H
#define KNIFE_MESSAGE_TEXTRENDER_SCREENADDR_H

#include "engine/entity.h"

namespace Knife { namespace Message { class TextRenderer; } }

extern "C" {
void *Knife_Message_TextRenderer_getScreenAddress(const Knife::Message::TextRenderer *self, s32 isBg, s32 index,
                                                 s32 bgMode, s32 a, s32 b); // 0x020a590c
}

#endif
