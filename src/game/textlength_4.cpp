#include "engine/functions.h"
#include "global.h"

// Functions in this file (original names from the debug build):
//   Knife::Message::TextLengthAnalyzer::onReadPlainText(Knife::Message::Text const*) (0x020a1748)

// Text as copied by value here (12 bytes); only the const member used by the analyzer is declared.
namespace Knife {
namespace Message {
class Text {
public:
    u32 words[3];
    u16 readFirstCharacter(u32 *pos) const;
};
}
}

extern "C" void *KnifeApp_getField20Address(void *app);
extern "C" s32 func_020c4ee4(void *font, u16 character);
extern "C" void *func_020c4f2c(void *font, s32 index);

// Text length analyzer (Knife::Message::TextLengthAnalyzer). Only the fields the functions use are named.
typedef struct KnifeTextLengthAnalyzer {
    void *vtbl;             // 0x00
    s16 maxLength;          // 0x04
    s16 unk_06;
    s16 unk_08;
    s16 lineIndex;          // 0x0a: index into counts
    u16 counts[0x20];       // 0x0c: one count per line
    u16 charCount;          // 0x4c
} KnifeTextLengthAnalyzer;

// TextLengthAnalyzer::onReadPlainText(Text const*) (0x020a1748): adds the width of the first character of the text to the
// current line and counts the character
extern "C" void Knife_Message_TextLengthAnalyzer_onReadPlainText(void *a, const void *text);
ARM void Knife_Message_TextLengthAnalyzer_onReadPlainText(void *a, const void *text) {
    KnifeTextLengthAnalyzer *self = (KnifeTextLengthAnalyzer *)a;
    Knife::Message::Text copy;
    u32 character;
    void *font;
    s32 index;
    s8 width;

    copy.words[0] = ((const u32 *)text)[0];
    copy.words[1] = ((const u32 *)text)[1];
    copy.words[2] = ((const u32 *)text)[2];
    character = copy.readFirstCharacter(0);
    font = KnifeApp_getField20Address(KnifeApp_getInstance());
    index = func_020c4ee4(font, (u16)character);
    if (index == 0xffff) {
        index = *(u16 *)(*(u8 **)font + 2);
    }
    width = *(s8 *)((u8 *)func_020c4f2c(font, index) + 2);
    self->counts[self->lineIndex] += (u16)width;
    self->charCount++;
}
