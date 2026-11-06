#include "knife/message/textrender_setup.h"

// Knife_Message_TextRender_setupFromMsgScrn (0x020a0f24): sets up the text render from a message screen info: copies its parameters, builds the
// canvas for the text area and draws the first character cells of the window into the screen buffer
void Knife_Message_TextRender_setupFromMsgScrn(KnifeTextRender *self, const TextRenderMsgScrn *info) {
    u32 width = (u32)info->widthPx >> 3;
    u32 height = info->heightCells;
    s32 charInfo;

    void *font;

    self->unk_76 = 0x10;
    self->unk_77 = 0;
    self->unk_78 = info->unk_18;
    self->selectCount = 0;
    *(u8 **)((u8 *)self + 0x2c) = info->screenBuffer;
    self->unk_82 = info->palette;
    charInfo = info->charInfo;
    Record_InitTable((u8 *)self + 4, info->charBase, width, height, 4);
    font = KnifeApp_getField20Address(KnifeApp_getInstance());
    *(void **)((u8 *)self + 0x1c) = (u8 *)self + 4;
    *(void **)((u8 *)self + 0x20) = font;
    *(u32 *)((u8 *)self + 0x24) = 1;
    *(u32 *)((u8 *)self + 0x28) = 1;
    func_020c6008(info->screenBuffer, width, height, 0, 0, 0x20, charInfo & 0x3ff, charInfo >> 12);
    Knife_Message_TextRender_setup(self);
}
