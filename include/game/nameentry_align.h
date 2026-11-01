#ifndef WIP_F_NAMEENTRY_ALIGN_H
#define WIP_F_NAMEENTRY_ALIGN_H

// Declarations used by nameentry_align.cpp (not in engine/functions.h).

#include "types.h"

extern "C" u16 nameEntryUIView_getTextFromIndex(void *self, s32 index);
extern "C" void *Knife_Message_GetRenderTarget(s32 pane);
extern "C" void *KnifeApp_getField20Address(void *self);
extern "C" u32 TextBox_FindRange(u8 *self, u32 value);
extern "C" u8 *TextBox_FindRangeEntry(u8 *self, u32 value);
extern "C" void Knife_Message_RedrawText(s32 index, const s32 *list);
extern "C" void DC_FlushRange(void *base, u32 size);
void subTaskSendScr(s16 index, void *data, u32 offset, u32 size);

extern "C" void nameEntryUIView_alignCenter(void *self, s32 index, s32 width);
extern "C" void *data_02180d9c;

#endif
