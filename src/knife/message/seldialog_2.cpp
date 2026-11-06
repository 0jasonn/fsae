#include "knife/message/seldialog.h"

// Knife::Message::selectionDialog::doModal(unsigned short, long, unsigned char, unsigned char) (0x020a1a88): opens the dialog
// for the message index: sets the animation state, loads the frame graphics for the dialog kind into the character buffer
// (the right part for a pointer dialog, the left part otherwise), measures the text to get the size and starts the choices
extern "C" void Knife_Message_selectionDialog_doModal(void *dialog, u16 msgId, s32 a, u8 b, u8 c) {
    KnifeSelectDialog *self = (KnifeSelectDialog *)dialog;
    TextRenderMsgScrn *scrn = (TextRenderMsgScrn *)self->msgScrn;
    SelDialogCharTable table = data_020de634;
    s32 frameSize;
    u8 *frame;
    u32 width;
    s32 w;
    s32 rows;
    s32 height;
    s32 cols;

    self->unk_68 = b;
    self->state = 2;
    self->unk_69 = c;
    self->unk_64 = msgId;
    self->timer = 0;
    *(s16 *)((u8 *)self + 0x6c) = 0x10;
    self->speed = 0x200;
    *(s16 *)((u8 *)self + 0x6e) = a;
    if (*((u8 *)scrn + 0x12) & 1) {
        frame = (u8 *)KnifeApp_getZeldaResource_08dde0(KnifeApp_getInstance(), &frameSize, 0x200 - 0x4a);
        self->unk_78 = table.v[*((u8 *)scrn + 0x17)];
        if (self->unk_69 != 0) {
            MIi_CpuCopyFast(frame + ((u32)((*((u8 *)scrn + 0x12) & 0xe) * frameSize) >> 1), scrn->charBase, 0xe0);
            MI_CpuFill8(scrn->charBase + 0xe0, (u8)self->unk_78, 0x20);
            scrn->charBase = scrn->charBase + 0x100;
        } else {
            MIi_CpuCopyFast(frame + 0x300, scrn->charBase + 0x1100, 0x100);
            MI_CpuFill8(scrn->charBase + 0x2e0 + 0x1000, (u8)self->unk_78, 0x20);
            scrn->charBase = scrn->charBase + 0x1300;
        }
        w = knife_GetFontStrWidth_04c2e0(msgId, 1, scrn->appWork);
        cols = *((u8 *)scrn + 0x14);
        {s32 lines = (w >> 16) & 0xff;
        rows = (w >> 24) * *((u8 *)scrn + 0x16);
        if (cols == 0) {
            cols = (u16)w;
        }
        height = rows + (lines << 1);}

        if (scrn->widthPx < cols) {
            cols = scrn->widthPx;
        }
        self->unk_70 = (cols + 7) / 8;
        scrn->heightCells = height;
        self->unk_72 = height;
    }
    Knife_Message_MessageSelect_init(self);
    *((u8 *)self + 7) = (self->visibleRequest != 0) ? 1 : 0;
    if (self->visibleRequest != 0) {
        SoundReq(0x43);
    }
    messageRequest[0] = 3;
}
