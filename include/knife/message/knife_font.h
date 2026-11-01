#ifndef WIP_B_KNIFE_FONT_H
#define WIP_B_KNIFE_FONT_H

#include "engine/functions.h"

// Callees of the knife font width helpers (dsd names where the function has no name yet).
extern "C" {
u32 Str_Length(const u8 *str);
void func_02005cc0(u8 *dst, const char *src, u32 length);
void *KnifeApp_getField20Address(void *app);
s32 TextBox_MeasureWidth(void *self, s32 length, u8 *buf);

s32 knife_GetFontStrWidth_04c34c(const char *text, s32 length);
u32 knife_GetFontStrWidth_04c2e0(s32 index, u8 flag, void *tokenizer);
}

#endif
