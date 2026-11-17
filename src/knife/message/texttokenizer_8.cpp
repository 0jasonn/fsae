#include "engine/functions.h"
#include "knife/message/text_tokenizer.h"

namespace Knife {
namespace Message {

// Appends the terminating token when the pool has room, then clears the reader.
void TextTokenizer::onEnd(bool, bool) {
    BOOL ok;
    u32 freeBytes;
    u8 *token;
    u8 *top;

    if (overflow != 0) {
        goto setOverflow;
    }
    freeBytes = poolSize - poolUsed;
    top = (u8 *)poolBase + freeBytes;
    if (freeBytes - tokenCount * 4 < 8) {
        ok = 0;
    } else {
        poolUsed += 4;
        token = top - 4;
        if (token != NULL) {
            *(void **)token = data_0211ad5c;
        }
        ok = 1;
        tokens[tokenCount] = (Token *)token;
        tokenCount += 1;
    }
    if (ok != 0) {
        goto clearState;
    }
setOverflow:
    overflow = 1;
clearState:
    textReader = NULL;
}

}
}
