#ifndef UI_FILESELUI_E_API_H
#define UI_FILESELUI_E_API_H

#include "engine/entity.h"

extern "C" {
void fileSelUIView_vfunc2(void *self);
s32 fileSelUIView_getText(void *self, void *text, u32 textId, s32 language);
}

#endif
