#include "ui/setuptext_e.h"

extern "C" s32 KnifeApp_getCurrentLanguage(void *app);

// modeSelUIView::setupTextRender() (0x020a9ce0): centres the common text (message 0x84f) on the two option targets,
// registers the targets with the text renderer and sends the cell buffer to the BG
void modeSelUIView_setupTextRender(ModeSelUIView *self) {
    u32 i;
    s32 width;
    s32 half;
    UIViewTextTarget *target;
    u8 *getter;
    u8 **cellBufferRef;

    Knife_Message_CleanupTextRenderer();
    width = knife_GetFontStrWidth_04c2e0(0x84f, 0, (u8 *)KnifeApp_getInstance() + 0x1bc);
    half = (0x100 - width) / 2;
    cellBufferRef = &data_02180da4;
    for (i = 0; i < 2; i++) {
        target = &data_02124bb4[i];
        target->msgId = 0x84f;
        target->column = half / 8;
        target->offsetX = half % 8;
        target->row = i * 6 + 5;
        target->offsetY = 2;
        target->height = 0xe;
        target->cellBase = *cellBufferRef + target->cellIndex * 0x20;
    }
    *(s32 *)(data_02124c50 + 0x38) = *(s32 *)(data_021806f0 + 0x6ac);
    getter = (u8 *)self->base.parent;
    if (getter != NULL) {
        getter += 0x30;
    }
    Knife::Message::SetupTextRenderer((const Knife::Message::TextRenderSceneInfo *)data_02124c50,
                                      (Knife::Message::Language)KnifeApp_getCurrentLanguage(KnifeApp_getInstance()),
                                      (Knife::Message::IExTextGetter *)getter);
    DC_FlushRange(*cellBufferRef + 0x6400, 0xa80);
    subTaskSendBgChar(1, *cellBufferRef + 0x6400, 0x6400, 0xa80);
}
