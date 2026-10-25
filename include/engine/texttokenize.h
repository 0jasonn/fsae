#ifndef WIP_D_TEXTTOKENIZE_H
#define WIP_D_TEXTTOKENIZE_H

#include "types.h"
#include "engine/text_tokenizer.h"
#include "engine/kmsgreader.h"

namespace Knife {
namespace Message {

// The localized text of a text id (124 bytes): the id, then one Text for each of the ten languages (filled by
// KMsgFileReader::convertTextHeaderToLocalizedText)
typedef struct LocalizedText {
    u32 textId;                     // 0x00
    Text texts[10];                 // 0x04: scheme, data and size of each language
} LocalizedText;

}
}

// Functions called from the tokenizer that are not declared in functions.h yet (the reviewer moves them there). The
// readData, ctor and dtor are TextReader members that are plain names in symbols.txt, so they are called as extern "C"
// with the reader as the first argument.
extern "C" {
BOOL Knife_Message_KMsgFileReader_findLocalizedTextByTextID(Knife::Message::KMsgFileReader *self, u32 textId, void *out);
void Knife_Message_TextReader_TextReader(void *self);
BOOL Knife_Message_TextReader_readData(void *self, const Knife::Message::Text *text, void *listener);
void Knife_Message_TextReader_dtor_TextReader_0a23e8(void *self);
}

#endif
