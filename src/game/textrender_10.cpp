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

// TextRenderer::TextRenderer() (0x020a4f44): sets the vtables, constructs the tokenizer and clears the pool
extern "C" void *Knife_Message_TextRenderer_TextRenderer(void *self);
ARM void *Knife_Message_TextRenderer_TextRenderer(void *self) {
    TextRenderer *renderer = (TextRenderer *)self;

    renderer->vtbl = data_021249ac;
    renderer->vtbl2 = data_02124a0c;
    Knife_Message_TextTokenizer_ctor_08e3b4(renderer->tokenizer);
    renderer->pool = NULL;
    renderer->initialized = 0;
    return self;
}

// TextRenderer::~TextRenderer() (0x020a4f80): the base destructor, finalizes and destroys the tokenizer
extern "C" void *Knife_Message_TextRenderer_dtor_TextRenderer_0a4f80(void *self);
ARM void *Knife_Message_TextRenderer_dtor_TextRenderer_0a4f80(void *self) {
    TextRenderer *renderer = (TextRenderer *)self;

    renderer->vtbl = data_021249ac;
    renderer->vtbl2 = data_02124a0c;
    renderer->finalize();
    Knife_Message_TextTokenizer_dtor_TextTokenizer_08e3f8(renderer->tokenizer);
    return self;
}

// TextRenderer::~TextRenderer() (0x020a4fb4): the deleting destructor, the same as 0x020a4f80 and then operator delete
extern "C" void *Knife_Message_TextRenderer_dtor_TextRenderer_0a4fb4(void *self);
ARM void *Knife_Message_TextRenderer_dtor_TextRenderer_0a4fb4(void *self) {
    TextRenderer *renderer = (TextRenderer *)self;

    renderer->vtbl = data_021249ac;
    renderer->vtbl2 = data_02124a0c;
    renderer->finalize();
    Knife_Message_TextTokenizer_dtor_TextTokenizer_08e3f8(renderer->tokenizer);
    operator delete(self);
    return self;
}

// TextRenderer::initialize(unsigned long) (0x020a4ff0): allocates the pool (a multiple of 0x20 bytes) and sets up the tokenizer
ARM BOOL TextRenderer::initialize(u32 size) {
    void *app;

    finalize();
    size &= ~0x1fu;
    if (size < 0x20) {
        return FALSE;
    }
    pool = EL_GetGlobalAdr(size, 0x20);
    if (pool == NULL) {
        finalize();
        return FALSE;
    }
    poolSize = size;
    app = KnifeApp_getInstance();
    if (Knife_Message_TextTokenizer_initialize(tokenizer, *(void **)((u8 *)app + 0x30), *(u32 *)((u8 *)app + 0x40), pool, poolSize) != 0) {
        initialized = 1;
        return TRUE;
    }
    finalize();
    return FALSE;
}

// TextRenderer::finalize() (0x020a507c): frees the pool, clears the buffers and the context
ARM void TextRenderer::finalize(void) {
    Knife_Message_TextTokenizer_finalize(tokenizer);
    if (pool != NULL) {
        func_0208e188(pool);
        pool = NULL;
    }
    poolSize = 0;
    MI_CpuFill8(unk_50, 0, 0x10);
    MI_CpuFill8(screenBuffer, 0, 0x20);
    unk_60 = 0;
    unk_64 = 0;
    unk_68 = 0;
    unk_98 = 0;
    unk_9c = 0;
    tokenList = NULL;
    tokenListCount = 0;
    flag94 = 0;
    flag95 = 0;
    unk_a0 = 0;
    unk_a8 = 0;
    unk_ac = 0;
    resetContext();
    initialized = 0;
}

}
}
