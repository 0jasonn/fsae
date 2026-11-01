#ifndef ENGINE_TEXT_BOX_API_H
#define ENGINE_TEXT_BOX_API_H

// Functions defined in src/engine/text_box*.cpp.

#include "engine/entity.h"

extern "C" {
u32 TextBox_LookupTable(u8 *self);
s32 TextBox_MeasureSegment(u8 *self, s32 base, u32 state, u32 *outState);
s32 TextBox_MeasureWidth(u8 *self, s32 base, u32 state, u32 unused);
void TextBox_SetKindHandler(u8 *self, u8 *arg);
}

#endif
