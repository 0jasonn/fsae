#ifndef WIP_E_SELDIALOG_E_H
#define WIP_E_SELDIALOG_E_H

#include "engine/functions.h"
#include "ui/selectiondialog.h"
#include "knife/message/textrender_setup.h"

typedef struct SelDialogCharTable {
    u32 v[16];
} SelDialogCharTable;
extern const SelDialogCharTable data_020de634;
extern u8 messageRequest[];

extern "C" {
void MI_CpuFill8(void *dst, u8 value, u32 size);
void Knife_Message_MessageSelect_init(void *self);
void MI_CpuCopy8(const void *src, void *dst, u32 size);
s32 knife_GetFontStrWidth_04c2e0(s32 msgId, u8 flag, void *work);

void func_020a1100(void *self, u8 value);
void func_020a1108(void *self, u8 value);
void Knife_Message_TextRender_clearCanvas(void *a, s32 mode);
void Knife_Message_MessageSelect_setup(void *self, u8 count, void *items, s32 flag);
}

#endif
