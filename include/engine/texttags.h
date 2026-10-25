#ifndef WIP_D_TEXTTAGS_H
#define WIP_D_TEXTTAGS_H

#include "types.h"
#include "engine/text_tokenizer.h"

// Declarations used by the TextTokenizer tag handlers (src/wip/D/texttags*.cpp and the parked attempts in scratch/agentD/nonmatching).

extern "C" {
extern char data_0211ad3c[];   // SelectTagToken vtable (4 bytes)
extern char data_0211ad9c[];   // WaitTagToken vtable
extern char data_0211adbc[];   // AutoTagToken vtable
extern char data_0211addc[];   // SyncTagToken vtable (4 bytes)
extern char data_0211adfc[];   // NextTagToken vtable
extern char data_0211ae3c[];   // TextSETagToken vtable
extern char data_0211ae5c[];   // PictTagToken vtable
extern char data_0211ae7c[];   // ButtonTagToken vtable
extern char data_0211ae9c[];   // BlankTagToken vtable
extern char data_0211aebc[];   // CenterTagToken vtable (4 bytes)
extern char data_0211aedc[];   // RightTagToken vtable (4 bytes)
extern char data_0211aefc[];   // SizeTagToken vtable
extern char data_0211af1c[];   // ColorTagToken vtable
extern char data_0211af3c[];   // RubyBeginTagToken vtable (16 bytes)
extern char data_0211af5c[];   // RubyEndTagToken vtable (4 bytes)

// Message formatting (0x0208fd50, parked: plain name in symbols.txt, so C linkage)
u32 Knife_Message_localizeValue(void *out, u32 outSize, const Knife::Message::ICharacterEncodingScheme *ces,
                                Knife::Message::Language language, s32 value);
void *Knife_Message_getCESObject_021770b4(void); // ces.cpp (0x0208fc6c)
void Knife_Message_TextReader_cancel(void *self);   // 0x020a25f8: TextReader::cancel (plain name, self first)
BOOL Knife_Message_TextTokenizer_duplicateText(void *self, Knife::Message::Text *dst, const Knife::Message::Text *src); // 0x0208f2a8
}

namespace Knife {
namespace Message {

// Knife::Message::IAppInfoGetter: the application's info. Slot 0 gives the number for a value tag, slot 1 fills a text
// for the player name tag. Declared here without a definition, so no vtable is emitted.
class IAppInfoGetter {
public:
    virtual s32 slot0(s32 value) const;
    virtual void slot1(s32 value, Text *text) const;
};

// Singular or plural form of a number in a language (0x0208fea4, message_localize.cpp): 0 singular, 1 plural
s32 getGrammaticalNumber(Language language, int value);

}
}

#endif
