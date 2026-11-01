#ifndef GAME_TEXTRENDER_API_H
#define GAME_TEXTRENDER_API_H

// Functions defined in src/game/textrender*.cpp.

#include "engine/entity.h"

extern "C" {
void Knife_Message_TextRender_clearCanvas(void *a, s32 mode);
void Knife_Message_TextRender_onReadBlankTag(void *a, s32 value);
void Knife_Message_TextRender_onReadNop(void *a);
void Knife_Message_TextRender_onReadSelectTag(void *a);
void Knife_Message_TextRender_setCenteringParam(void *a, s32 count, const u16 *values);
void Knife_Message_TextRender_setField83(void *a, u8 value);
void Knife_Message_TextRender_setFlag83On(void *a);
void Knife_Message_TextRender_setup(void *a);
u32 Knife_Message_TextRenderer_getField50(void *a, s32 index);
}

#endif
