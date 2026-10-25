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

// TextTokenizer::onReadRubyEndTag() (0x0208f21c)
ARM void TextTokenizer::onReadRubyEndTag(void) {
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
            *(void **)token = data_0211af5c;
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
