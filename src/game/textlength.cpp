#include "engine/functions.h"
#include "global.h"
#include "game/textlength_api.h"
#include "game/textlength.h"

// Functions in this file (original names from the debug build):
//   Knife::Message::TextLengthAnalyzer::TextLengthAnalyzer() (0x020a16c4)

extern u8 data_0211ede0[]; // TextLengthAnalyzer vtable

// TextLengthAnalyzer::TextLengthAnalyzer() (0x020a16c4): sets the vtable and clears the counts
void Knife_Message_TextLengthAnalyzer_TextLengthAnalyzer(void *a) {
    KnifeTextLengthAnalyzer *self = (KnifeTextLengthAnalyzer *)a;
    s32 i;

    self->vtbl = data_0211ede0;
    self->maxLength = 0;
    for (i = 0; i < 0x20; i++) {
        self->counts[i] = 0;
    }
    self->nonEmptyLines = 0;
    self->emptyLines = 0;
    self->lineIndex = 0;
    self->charCount = 0;
}

// Functions in this file (original names from the debug build):
//   TextLengthAnalyzer::onTerminate() (0x020a1704)

// TextLengthAnalyzer::onTerminate() (0x020a1704): the same count step as onReadNewLine, without the zero test
void Knife_Message_TextLengthAnalyzer_onTerminate(void *a) {
    KnifeTextLengthAnalyzer *self = (KnifeTextLengthAnalyzer *)a;

    if (self->counts[self->lineIndex] > self->maxLength) {
        self->maxLength = self->counts[self->lineIndex];
    }
    if (self->counts != 0) {
        self->nonEmptyLines++;
    } else {
        self->emptyLines++;
    }
    self->lineIndex++;
}

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
extern "C" s32 TextBox_FindRange(void *font, u16 character);
extern "C" void *TextBox_FindRangeEntry(void *font, s32 index);

// TextLengthAnalyzer::onReadPlainText(Text const*) (0x020a1748): adds the width of the first character of the text to the
// current line and counts the character
extern "C" void Knife_Message_TextLengthAnalyzer_onReadPlainText(void *a, const void *text);
void Knife_Message_TextLengthAnalyzer_onReadPlainText(void *a, const void *text) {
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
    index = TextBox_FindRange(font, (u16)character);
    if (index == 0xffff) {
        index = *(u16 *)(*(u8 **)font + 2);
    }
    width = *(s8 *)((u8 *)TextBox_FindRangeEntry(font, index) + 2);
    self->counts[self->lineIndex] += (u16)width;
    self->charCount++;
}

// Functions in this file (original names from the debug build):
//   TextLengthAnalyzer::onReadNewLine() (0x020a17e8)

// TextLengthAnalyzer::onReadNewLine() (0x020a17e8): closes the current line and counts it as empty or not
void Knife_Message_TextLengthAnalyzer_onReadNewLine(void *a) {
    KnifeTextLengthAnalyzer *self = (KnifeTextLengthAnalyzer *)a;

    if (self->counts[self->lineIndex] > self->maxLength) {
        self->maxLength = self->counts[self->lineIndex];
    }
    if (self->counts[self->lineIndex] != 0) {
        self->nonEmptyLines++;
    } else {
        self->emptyLines++;
    }
    self->lineIndex++;
}
