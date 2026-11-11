#include "knife/message/msgtextrender.h"

extern u8 data_0217d350[];        // +4: byte of the scene info used by the glyph drawing
extern char data_020de464[];      // glyph drawing table of the renderer
extern const u32 data_020de480[]; // sound request of each voice

// Knife::Message::MessageTextRender::onReadPlainText(Text const*) (0x020a0640), plain name: draws the first character
// of the text at the current position and advances the position. While the window closes it queues the line changes;
// otherwise a character other than 0x120 plays the sound of the voice once per step.
void Knife_Message_MessageTextRender_onReadPlainText(Knife::Message::MessageTextRender *self, const Knife::Message::Text *text) {
    Knife::Message::Text copy;
    u32 ch;
    void *field;
    s16 advance;
    KNIFE_MSGSYS *msg;

    copy = *text;
    msg = (KNIFE_MSGSYS *)self->sceneInfo;
    if (msg->unk_d8[0] & 0x80) {
        Knife_palletChange(msg, msg->unk_d8[0] & 0x3f);
        ((KNIFE_MSGSYS *)self->sceneInfo)->unk_d8[0] = 0;
    }
    ch = copy.readFirstCharacter(0);
    field = KnifeApp_getField20Address(KnifeApp_getInstance());
    *(const char **)((u8 *)self + 0x20) = data_020de464;
    *(u32 *)(data_0217d350 + 4) = ((KNIFE_MSGSYS *)self->sceneInfo)->unk_2b[0];
    advance = (s16)func_020c5e00(&self->canvas, field, self->offsetX, self->offsetY + (s8)self->field35, 1, (u16)ch);
    self->field36 = 1;
    self->offsetX = self->offsetX + advance;
    msg = (KNIFE_MSGSYS *)self->sceneInfo;
    if (msg->openMode == 2) {
        msg->stepTimer = 0x78;
        ((KNIFE_MSGSYS *)self->sceneInfo)->lineQueue[0] = 0x5e;
        ((KNIFE_MSGSYS *)self->sceneInfo)->lineQueue[1] = 0x73;
    } else if (ch != 0x120 && msg->unk_0d != 0 && msg->unk_de == 0) {
        msg->unk_de = 4;
        SoundReq(data_020de480[((KNIFE_MSGSYS *)self->sceneInfo)->unk_0d]);
    }
    ((KNIFE_MSGSYS *)self->sceneInfo)->unk_d8[1] = 1;
}
