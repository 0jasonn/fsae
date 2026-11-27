#ifndef UI_NAMEENTRY_ALIGN_H
#define UI_NAMEENTRY_ALIGN_H

// Name entry text alignment and keyboard display.

#include "types.h"
#include "ui/file_selection_buffers.h"

extern "C" u16 nameEntryUIView_getTextFromIndex(void *self, s32 index);
extern "C" void *Knife_Message_GetRenderTarget(s32 pane);
extern "C" u32 TextBox_FindRange(u8 *self, u32 value);
extern "C" u8 *TextBox_FindRangeEntry(u8 *self, u32 value);
extern "C" void Knife_Message_RedrawText(s32 index, const s32 *list);

extern "C" void nameEntryUIView_alignCenter(void *self, s32 index, s32 width);
extern "C" void nameEntryUIView_keybord_disp(void *self);

#endif
