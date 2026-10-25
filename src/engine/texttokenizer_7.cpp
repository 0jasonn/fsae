#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/text_tokenizer.h"
#include "engine/kmsgreader_d.h"

// Knife::Message::TextTokenizer::initialize (0x0208e450) and finalize (0x0208e49c). Both are plain extern "C" functions
// taking the tokenizer as self: the callers in knife_app_4.cpp, textrender_10.cpp and texttokenizer.cpp use the plain
// names.

// TextTokenizer::initialize(void const*, unsigned long, void*, unsigned long) (0x0208e450): finalizes the tokenizer,
// reads the message file from data, and sets the pool when the file was accepted. FALSE when the file is not valid.
extern "C" BOOL Knife_Message_TextTokenizer_initialize(void *self, const void *data, u32 size, void *pool, u32 poolSize);
ARM BOOL Knife_Message_TextTokenizer_initialize(void *self, const void *data, u32 size, void *pool, u32 poolSize) {
    Knife::Message::TextTokenizer *tokenizer;

    tokenizer = (Knife::Message::TextTokenizer *)self;
    Knife_Message_TextTokenizer_finalize(self);
    if (Knife_Message_KMsgFileReader_initialize(&tokenizer->msgFile, data, size) == 0) {
        return 0;
    }
    tokenizer->changeMemoryPool(pool, poolSize);
    return 1;
}

// TextTokenizer::finalize() (0x0208e49c): cleans up the tokens, finalizes the message file and clears the state
extern "C" void Knife_Message_TextTokenizer_finalize(void *self);
ARM void Knife_Message_TextTokenizer_finalize(void *self) {
    Knife::Message::TextTokenizer *tokenizer;

    tokenizer = (Knife::Message::TextTokenizer *)self;
    tokenizer->cleanupTokens();
    tokenizer->msgFile.finalize();
    tokenizer->poolBase = NULL;
    tokenizer->poolSize = 0;
    tokenizer->poolUsed = 0;
    tokenizer->tokens = NULL;
    tokenizer->tokenCount = 0;
    tokenizer->appInfo = NULL;
    tokenizer->textId = 0;
    tokenizer->language = -1;
    tokenizer->overflow = 0;
}
