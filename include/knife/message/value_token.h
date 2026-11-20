#ifndef KNIFE_MESSAGE_VALUE_TOKEN_H
#define KNIFE_MESSAGE_VALUE_TOKEN_H

#include "types.h"
#include "knife/message/text_tokenizer.h"

namespace Knife {
namespace Message {

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

}
}

#endif
