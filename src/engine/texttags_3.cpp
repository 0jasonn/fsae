#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/text_tokenizer.h"
#include "engine/texttags.h"

// Knife::Message::TextTokenizer tag handlers, 0x0208e8d4 to 0x0208f21c. Each handler pushes one token onto the pool
// (vtable, then the tag value when it has one) and records it in the token list. When the pool has no room it cancels
// the reader and sets the overflow flag. 8-byte tokens need 12 bytes free (with the list entry), 4-byte tokens need 8,
// the ruby begin token needs 20 and holds a copy of its text.

namespace Knife {
namespace Message {

// TextTokenizer::onReadValueTag(int) (0x0208ec90): localizes the number that slot 0 of the app info gives and passes
// the text to onReadPlainText
ARM void TextTokenizer::onReadValueTag(s32 value) {
    u8 buf[0x40];
    Text text;
    s32 number;
    u32 length;

    number = appInfo->slot0(value);
    length = Knife_Message_localizeValue(buf, 0x40, (const ICharacterEncodingScheme *)Knife_Message_getCESObject_021770b4(),
                                         (Language)language, number);
    text.clear();
    text.ces = (ICharacterEncodingScheme *)Knife_Message_getCESObject_021770b4();
    text.data = buf;
    text.size = length;
    onReadPlainText(&text);
}

}
}
