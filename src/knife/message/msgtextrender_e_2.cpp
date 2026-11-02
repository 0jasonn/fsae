#include "knife/message/msgtextrender_e.h"

extern u8 data_0217d350[];             // +4: byte of the scene info used by the glyph drawing
extern char data_020de464[];      // glyph drawing table of the renderer
extern const u32 data_020de480[];      // sound request of each voice

// Knife::Message::MessageTextRender::onReadPictTag(Pictogram) (0x020a0b64), plain name: pictogram 0x1c switches the frame
// off; the others set the palette of the window and draw the icon at the current position
void Knife_Message_MessageTextRender_onReadPictTag(Knife::Message::MessageTextRender *self, s32 pictogram) {
    MsgPictogramTable table = data_020de58c;
    u16 packed = table.entry[pictogram];
    u16 cell;
    BOOL alt;
    u8 *sheet;
    KNIFE_MSGSYS *msg;

    if (pictogram == 0x1c) {
        Knife_msgFrameDma((KNIFE_MSGSYS *)self->sceneInfo, 0);
        return;
    }
    cell = ((packed & 0xc0) << 6) | 0x400 | (packed & 0x3f);
    msg = (KNIFE_MSGSYS *)self->sceneInfo;
    msg->unk_d8[0] = msg->palletBits | 0x80;
    Knife_palletChange((KNIFE_MSGSYS *)self->sceneInfo, (u8)(((cell & 0xf000) >> 8) | 0x81));
    ((KNIFE_MSGSYS *)self->sceneInfo)->unk_d8[1] = 0;
    alt = (data_0212c7c8.unk_8e == 1 || data_0212c7c8.unk_8e == 4);
    if (alt) {
        sheet = KnifeApp_getZeldaResource_08ddcc(KnifeApp_getInstance(), 0x286);
    } else {
        sheet = KnifeApp_getZeldaResource_08ddcc(KnifeApp_getInstance(), 0x1be);
    }
    IconToCanvas(sheet + (((u32)cell << 24) >> 17), &self->canvas, self->offsetX, self->offsetY + (s8)self->field35);
    self->offsetX = self->offsetX + 0x10;
}

// Knife::Message::MessageTextRender::onReadButtonTag(Button) (0x020a0c90), plain name: sets the window palette and draws the
// icon of the button (buttons 3 and 4 use fixed cells)
void Knife_Message_MessageTextRender_onReadButtonTag(Knife::Message::MessageTextRender *self, s32 button) {
    MsgButtonTable table = data_020de570;
    u16 packed = table.entry[button];
    u16 cell;
    BOOL alt;
    u8 *sheet;
    KNIFE_MSGSYS *msg;

    cell = ((packed & 0xc0) << 6) | 0x400 | (packed & 0x3f);
    msg = (KNIFE_MSGSYS *)self->sceneInfo;
    msg->unk_d8[0] = msg->palletBits | 0x80;
    Knife_palletChange((KNIFE_MSGSYS *)self->sceneInfo, (u8)(((cell & 0xf000) >> 8) | 0x81));
    ((KNIFE_MSGSYS *)self->sceneInfo)->unk_d8[1] = 0;
    alt = (data_0212c7c8.unk_8e == 1 || data_0212c7c8.unk_8e == 4);
    if (alt) {
        sheet = KnifeApp_getZeldaResource_08ddcc(KnifeApp_getInstance(), 0x286);
    } else {
        sheet = KnifeApp_getZeldaResource_08ddcc(KnifeApp_getInstance(), 0x1be);
    }
    if (button == 3) {
        cell = 0x21;
    }
    if (button == 4) {
        cell = 0x22;
    }
    IconToCanvas(sheet + (((u32)cell << 24) >> 17), &self->canvas, self->offsetX, self->offsetY + (s8)self->field35);
    self->offsetX = self->offsetX + 0x10;
}
