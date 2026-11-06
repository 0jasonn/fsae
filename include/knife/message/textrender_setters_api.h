#ifndef GAME_TEXTRENDER_SETTERS_E_API_H
#define GAME_TEXTRENDER_SETTERS_E_API_H

// Functions defined in src/game/textrender_setters_e*.cpp.

#include "engine/entity.h"

extern "C" {
void Knife_Message_TextRenderer_setField50_54(void *self, s32 a, s32 b);
void Knife_Message_TextRenderer_setField58(void *self, s32 value);
void Knife_Message_TextRenderer_setField64(void *self, s32 value);
void Knife_Message_TextRenderer_setField68(void *self, s32 value);
}

#endif
