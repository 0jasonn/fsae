#include "engine/functions.h"
#include "global.h"

// Functions in this file (original names from the debug build):
//   TextRender::onReadPlainText(Text const*) (0x020a1244)

extern u8 data_020de5cc[]; // table stored at +0x18 of the renderer
extern u8 data_0217d354[]; // word the plain text stores the flag byte into
// Knife::Message::Text members used here (the class is in engine/text_tokenizer.h, which clashes with the game headers)
namespace Knife {
namespace Message {
class Text {
public:
    void clear(void);
    u32 readFirstCharacter(u32 *out) const;
};
}
}
extern "C" void *KnifeApp_getField20Address(void *app);
extern "C" s32 func_020c5e00(void *self, void *field, s16 x, s16 y, s32 mode, u16 value);

// Copy of a Knife::Message::Text (three words)
typedef struct KnifeMsgTextPlain {
    u32 a;
    u32 b;
    u32 c;
} KnifeMsgTextPlain;

// Text renderer fields used by onReadPlainText
typedef struct KnifeTextRenderPlain {
    u8 unk_00[0x04];
    u8 sub[0x14];       // 0x04: object passed to func_020c5e00
    void *table;        // 0x18: set to data_020de5cc
    u8 unk_1c[0x30 - 0x1c];
    s16 posX;           // 0x30
    s16 posY;           // 0x32
    u8 unk_34[0x78 - 0x34];
    u8 flag78;          // 0x78
    u8 unk_79[0x84 - 0x79];
    u8 flag84;          // 0x84: set to 1
} KnifeTextRenderPlain;

extern "C" void Knife_Message_TextRender_onReadPlainText(void *a, const void *text);
ARM void Knife_Message_TextRender_onReadPlainText(void *a, const void *text) {
    KnifeTextRenderPlain *self = (KnifeTextRenderPlain *)a;
    const KnifeMsgTextPlain *src = (const KnifeMsgTextPlain *)text;
    KnifeMsgTextPlain copy;
    s32 ch;
    void *field;
    s16 advance;

    copy.a = src->a;
    copy.b = src->b;
    copy.c = src->c;
    ch = ((const Knife::Message::Text *)&copy)->readFirstCharacter(0);
    field = KnifeApp_getField20Address(KnifeApp_getInstance());
    self->table = data_020de5cc;
    *(u32 *)data_0217d354 = self->flag78;
    advance = (s16)func_020c5e00((u8 *)self + 4, field, self->posX, self->posY, 1, (u16)ch);
    self->flag84 = 1;
    self->posX = self->posX + advance;
}
