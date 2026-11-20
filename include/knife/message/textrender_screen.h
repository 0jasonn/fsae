#ifndef KNIFE_MESSAGE_TEXTRENDER_SCREEN_H
#define KNIFE_MESSAGE_TEXTRENDER_SCREEN_H

#include "engine/entity.h"

namespace Knife { namespace Message { class TextRenderer; } }

extern "C" {
void *func_020a59ac(Knife::Message::TextRenderer *self, s32 isBg, s32 index);
}

#endif
