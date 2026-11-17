#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "knife/message/text_tokenizer.h"
#include "knife/message/texttags.h"

// Knife::Message::TextTokenizer tag handlers with one value: the token (vtable word and the value) is allocated from the
// pool, whose objects grow down from the top while the token pointer array grows up from the bottom. 12 free bytes are
// needed (8 for the token, 4 for its list entry). When the pool has no room the reader is cancelled and the overflow flag
// is set.

namespace Knife {
namespace Message {

// Allocates and links a two word token with the given vtable word; false when the pool is full.
static inline BOOL allocValueToken(TextTokenizer *self, const char *vtable, u8 **out) {
    u32 freeBytes = self->poolSize - self->poolUsed;
    u8 *top = (u8 *)self->poolBase + freeBytes;
    u8 *token;

    if (freeBytes - self->tokenCount * 4 < 12) {
        return 0;
    }
    self->poolUsed += 8;
    token = top - 8;
    if (token != NULL) {
        *(const void **)token = vtable;
        *(s32 *)(token + 4) = 0;
    }
    *out = token;
    self->tokens[self->tokenCount] = (Token *)token;
    self->tokenCount += 1;
    return 1;
}

// TextTokenizer::onReadBlankTag(long) (0x0208ed98)
void TextTokenizer::onReadBlankTag(s32 value) {
    u8 *token = NULL;

    if (allocValueToken(this, data_0211ae9c, &token)) {
        *(s32 *)(token + 4) = value;
        return;
    }
    Knife_Message_TextReader_cancel(textReader);
    overflow = 1;
}

}
}
