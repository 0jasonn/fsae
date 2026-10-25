#include "engine/functions.h"
#include "global.h"
#include "game/textrender.h"

// Functions in this file (original names from the debug build):
//   TextRenderer::TextRenderer() (0x020a4f44), ~TextRenderer() (0x020a4f80, base, and 0x020a4fb4, deleting),
//   initialize (0x020a4ff0), finalize (0x020a507c), setScreenBuffer (0x020a511c), getNumberOfTokens (0x020a5340),
//   getToken (0x020a5354), resetContext (0x020a536c)

namespace Knife {
namespace Message {

extern "C" u8 data_021249ac[]; // vtable of TextRenderer
extern "C" u8 data_02124a0c[]; // vtable of the second base
extern "C" void *Knife_Message_TextTokenizer_ctor_08e3b4(void *self);
extern "C" void *Knife_Message_TextTokenizer_dtor_TextTokenizer_08e3f8(void *self);
extern "C" void Knife_Message_TextTokenizer_finalize(void *self);
extern "C" BOOL Knife_Message_TextTokenizer_initialize(void *self, void *a, u32 b, void *pool, u32 size);
extern "C" void MI_CpuFill8(void *dst, u8 value, u32 size);
extern "C" void *EL_GetGlobalAdr(u32 offset, u32 size);

// TextRenderer::getNumberOfTokens() const (0x020a5340): the count of the token list, or of the tokenizer
ARM s32 TextRenderer::getNumberOfTokens(void) const {
    if (tokenList != NULL) {
        return tokenListCount;
    }
    return *(s32 *)(tokenizer + 0x24);
}

// TextRenderer::getToken(int) const (0x020a5354): the token at index of the token list, or of the tokenizer
ARM void *TextRenderer::getToken(s32 index) const {
    if (tokenList != NULL) {
        return ((void **)tokenList)[index];
    }
    return ((void **)*(void **)(tokenizer + 0x20))[index];
}

// TextRenderer::resetContext() (0x020a536c): clears the counters of the current context
ARM void TextRenderer::resetContext(void) {
    unk_a4 = 0;
    unk_b4 = 0;
    unk_b0 = 0;
    unk_b8 = 0;
}

}
}
