#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "knife/message/text_tokenizer.h"
#include "knife/message/texttags.h"

using namespace Knife::Message;

// TextTokenizer::duplicateText(Text*, Text const*) (0x0208f2a8)
BOOL Knife_Message_TextTokenizer_duplicateText(void *selfArg, Text *dst, const Text *src) {
    TextTokenizer *self = (TextTokenizer *)selfArg;
    u32 aligned;
    u32 freeBytes;
    u32 room;
    u8 *data;
    u8 *top;

    aligned = (src->size + 3) & ~3;
    freeBytes = self->poolSize - self->poolUsed;
    room = freeBytes - self->tokenCount * 4;
    top = (u8 *)self->poolBase + freeBytes;
    dst->ces = NULL;
    dst->data = NULL;
    dst->size = 0;
    if (aligned > room) {
        return 0;
    }
    data = top - aligned;
    self->poolUsed += aligned;
    CopyBytes(data, src->data, src->size);
    dst->ces = src->ces;
    dst->data = data;
    dst->size = src->size;
    return 1;
}

