#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "knife/message/text_tokenizer.h"
#include "knife/message/texttags.h"

// Knife::Message::TextTokenizer::onReadRubyBeginTag: the ruby begin token (vtable word and a Text, 16 bytes) is allocated
// from the token pool (20 free bytes needed with its list entry) and receives a copy of the ruby text. When the pool has
// no room, or the copy fails, the reader is cancelled and the overflow flag is set.

namespace Knife {
namespace Message {

static inline BOOL allocRubyToken(TextTokenizer *self, u8 **out) {
    u32 freeBytes = self->poolSize - self->poolUsed;
    u8 *top = (u8 *)self->poolBase + freeBytes;
    u8 *token;

    if (freeBytes - self->tokenCount * 4 < 0x14) {
        return 0;
    }
    self->poolUsed += 0x10;
    token = top - 0x10;
    if (token != NULL) {
        *(void **)token = data_0211af3c;
        ((Text *)(token + 4))->clear();
        *(s32 *)(token + 4) = 0;
        *(s32 *)(token + 8) = 0;
        *(s32 *)(token + 0xc) = 0;
    }
    *out = token;
    self->tokens[self->tokenCount] = (Token *)token;
    self->tokenCount += 1;
    return 1;
}

// TextTokenizer::onReadRubyBeginTag(Text const*) (0x0208f118)
void TextTokenizer::onReadRubyBeginTag(const Text *text) {
    Text copy;
    u8 *token;

    copy.clear();
    token = NULL;
    if (!allocRubyToken(this, &token)) {
        Knife_Message_TextReader_cancel(textReader);
        overflow = 1;
        return;
    }
    if (Knife_Message_TextTokenizer_duplicateText(this, &copy, text) == 0) {
        Knife_Message_TextReader_cancel(textReader);
        overflow = 1;
        return;
    }
    *(Text *)(token + 4) = copy;
}

}
}
