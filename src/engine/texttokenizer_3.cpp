#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/text_tokenizer.h"

// Knife::Message::TextTokenizer, 0x0208e5c4 to 0x0208e6bc: the string overloads of tokenize, changeMemoryPool and the
// slot 0 hook (onBegin). onEnd (0x0208e6bc) is parked in scratch/agentD/nonmatching. The tokenize(unsigned long, ...)
// overload at 0x0208e4e0 is not in this unit yet.

namespace Knife {
namespace Message {

// TextTokenizer::tokenize(unsigned short const*) (0x0208e5c4): wraps the string in a Text and tokenizes that
ARM BOOL TextTokenizer::tokenize(const u16 *str) {
    Text text;

    Knife_Message_Text_Text(&text, str);

    return tokenize(&text);
}

// TextTokenizer::tokenize(Text const*) (0x0208e5f0): clears the source fields, runs onBegin, onReadPlainText and onEnd.
// The result is FALSE once the pool overflowed.
ARM BOOL TextTokenizer::tokenize(const Text *text) {
    s32 zero;

    cleanupTokens();
    zero = 0;
    textId = zero;
    language = zero - 1;
    appInfo = (const IAppInfoGetter *)zero;
    textReader = (TextReader *)zero;
    onBegin(0, text);
    onReadPlainText(text);
    onEnd(false, false);
    if (overflow == 0) {
        return 1;
    }
    return 0;
}

// TextTokenizer::changeMemoryPool(void*, unsigned long) (0x0208e670): sets the pool, clears it and empties the token list
ARM void TextTokenizer::changeMemoryPool(void *pool, u32 size) {
    cleanupTokens();
    poolBase = pool;
    poolSize = size;
    poolUsed = 0;
    Mem_Set(pool, 0, size);
    tokenCount = 0;
    tokens = (Token **)poolBase;
}

// Slot 0 of the vtable (0x0208e6b4): stores the reader. The text argument is not used.
ARM void TextTokenizer::onBegin(TextReader *newReader, const Text *text) {
    textReader = newReader;
}

}
}
