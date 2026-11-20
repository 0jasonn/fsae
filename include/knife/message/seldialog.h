#ifndef WIP_E_SELDIALOG_E_H
#define WIP_E_SELDIALOG_E_H

#include "engine/functions.h"
#include "knife/message/selectiondialog.h"
#include "knife/message/textrender_setup.h"

typedef struct SelDialogCharTable {
    u32 v[16];
} SelDialogCharTable;
extern const SelDialogCharTable data_020de634;

extern "C" {
s32 knife_GetFontStrWidth_04c2e0(s32 msgId, u8 flag, void *work);

void Knife_Message_MessageSelect_setup(void *self, u8 count, void *items, s32 flag);
}

#endif
