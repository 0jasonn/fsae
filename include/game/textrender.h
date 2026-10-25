#ifndef WIP_E_TEXTRENDER_H
#define WIP_E_TEXTRENDER_H

#include "engine/functions.h"

namespace Knife {
namespace Message {

// Text renderer (Knife::Message::TextRenderer). Its text tokenizer is embedded at +0x0c (TextTokenizer, 0x3c bytes; see
// engine/text_tokenizer.h). Only the fields the functions matched so far use are named.
class TextRenderer {
public:
    BOOL initialize(u32 poolSize);
    void finalize(void);
    void setScreenBuffer(void *buffer, bool isObj, s32 index);
    s32 getNumberOfTokens(void) const;
    void *getToken(s32 index) const;
    void resetContext(void);

    void *vtbl;                 // 0x00
    void *vtbl2;                // 0x04: second base (the thunks subtract 4 from this)
    u8 initialized;             // 0x08: set by initialize, cleared by finalize
    u8 unk_09[3];
    u8 tokenizer[0x3c];         // 0x0c: TextTokenizer
    void *pool;                 // 0x48: memory pool of the tokenizer
    u32 poolSize;               // 0x4c
    u8 unk_50[0x10];            // 0x50: cleared by finalize
    u32 unk_60;                 // 0x60
    u32 unk_64;                 // 0x64: set by 0x020a510c
    u32 unk_68;                 // 0x68: set by 0x020a5114
    void *screenBuffer[8];      // 0x6c: screen buffers (4 for BG, 4 for OBJ, see setScreenBuffer)
    void *tokenList;            // 0x8c: token list when set, otherwise the tokenizer's list
    s32 tokenListCount;         // 0x90
    u8 flag94;                  // 0x94
    u8 flag95;                  // 0x95
    u32 unk_98;                 // 0x98
    u32 unk_9c;                 // 0x9c
    u32 unk_a0;                 // 0xa0
    u32 unk_a4;                 // 0xa4: cleared by resetContext
    u32 unk_a8;                 // 0xa8
    u32 unk_ac;                 // 0xac
    u32 unk_b0;                 // 0xb0: cleared by resetContext
    u32 unk_b4;                 // 0xb4: cleared by resetContext
    u32 unk_b8;                 // 0xb8: cleared by resetContext
};

}
}

#endif
