#include "knife/message/seldialog.h"

// Knife::Message::selectionDialog::dispMessage() (0x020a1fbc): shows the message of the dialog. The message screen info of
// the dialog is copied, moved to the middle of the screen (by the size of the choices) and given to the text render of the
// application, which draws the text; then the choice list is set up from the result
void Knife_Message_selectionDialog_dispMessage(void *dialog) {
    KnifeSelectDialog *self = (KnifeSelectDialog *)dialog;
    TextRenderMsgScrn info;
    u8 *app;

    MI_CpuCopy8(self->msgScrn, &info, 0x38);
    if (info.unk_12[1] & 0x10) {
        info.screenBuffer += (0xc - (self->unk_72 / 2 + 1)) << 6;
    }
    info.screenBuffer += 0x40;
    info.charInfo += 8;
    if (info.unk_12[1] & 1) {
        knife_GetFontStrWidth_04c2e0(self->unk_64, 0, info.appWork);
        info.screenBuffer += (0x10 - self->unk_70 / 2) << 1;
        info.widthPx = self->unk_70 << 3;
    }
    app = (u8 *)KnifeApp_getInstance();
    func_020a1100(app + 0x80, 2);
    func_020a1108(app + 0x80, 0x10);
    Knife_Message_TextRender_setupCanvas((KnifeTextRender *)(app + 0x80), &info, self->unk_64);
    Knife_Message_TextRender_clearCanvas(app + 0x80, self->unk_78);
    KnifeApp_MessageRequest(KnifeApp_getInstance(), self->unk_64, info.appWork, app + 0x80, 0);
    *(u32 *)((u8 *)self + 0x60) = *(u32 *)(app + 0xac);
    Knife_Message_MessageSelect_setup(self, app[0xf9], app + 0xfa, 1);
    *((u8 *)self + 4) = self->unk_68;
}
