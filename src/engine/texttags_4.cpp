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

// TextTokenizer::onReadPlayerNameTag(int) (0x0208ee24): slot 1 of the app info fills a text for the value
ARM void TextTokenizer::onReadPlayerNameTag(s32 value) {
    Text text;

    text.clear();
    appInfo->slot1(value, &text);
    onReadPlainText(&text);
}

// TextTokenizer::onReadSPSwitchTag(int, Text const*, Text const*) (0x0208ee74): the second text when the number
// given by slot 0 is plural, the first otherwise
ARM void TextTokenizer::onReadSPSwitchTag(s32 value, const Text *first, const Text *second) {
    Text text;
    s32 number;

    text.clear();
    number = getGrammaticalNumber((Language)language, appInfo->slot0(value));
    if (number == 0) {
        text = *first;
    } else {
        text = *second;
    }
    onReadPlainText(&text);
}

// TextTokenizer::onReadCenterTag() (0x0208ef00)
ARM void TextTokenizer::onReadCenterTag(void) {
    BOOL ok;
    u32 freeBytes;
    u8 *token;
    u8 *top;

    freeBytes = poolSize - poolUsed;
    top = (u8 *)poolBase + freeBytes;
    if (freeBytes - tokenCount * 4 < 8) {
        ok = 0;
    } else {
        poolUsed += 4;
        token = top - 4;
        if (token != NULL) {
            *(void **)token = data_0211aebc;
        }
        ok = 1;
        tokens[tokenCount] = (Token *)token;
        tokenCount += 1;
    }
    if (ok != 0) {
        return;
    }
    Knife_Message_TextReader_cancel(textReader);
    overflow = 1;
}

// TextTokenizer::onReadRightTag() (0x0208ef80)
ARM void TextTokenizer::onReadRightTag(void) {
    BOOL ok;
    u32 freeBytes;
    u8 *token;
    u8 *top;

    freeBytes = poolSize - poolUsed;
    top = (u8 *)poolBase + freeBytes;
    if (freeBytes - tokenCount * 4 < 8) {
        ok = 0;
    } else {
        poolUsed += 4;
        token = top - 4;
        if (token != NULL) {
            *(void **)token = data_0211aedc;
        }
        ok = 1;
        tokens[tokenCount] = (Token *)token;
        tokenCount += 1;
    }
    if (ok != 0) {
        return;
    }
    Knife_Message_TextReader_cancel(textReader);
    overflow = 1;
}

}
}
