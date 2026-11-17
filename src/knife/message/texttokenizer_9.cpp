#include "engine/functions.h"
#include "knife/message/text_tokenizer.h"
#include "knife/message/texttags.h"

namespace Knife {
namespace Message {

// Records a newline token or cancels the reader when the pool overflows.
void TextTokenizer::onReadNewLine(void) {
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
            *(void **)token = data_0211ae1c;
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
