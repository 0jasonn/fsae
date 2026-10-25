#ifndef WIP_E_MESSAGE_E_H
#define WIP_E_MESSAGE_E_H

// Knife::Message classes used by the implementer E units (text renderer, text reader, selection dialog, pictogram).
// Layouts follow the matched code; only the fields the functions use are named. The types here are file-independent
// copies: include/game/textrender.h keeps its own partial TextRenderer.

#include "engine/functions.h"
#include "engine/text_tokenizer.h"

namespace Knife {
namespace Message {

// Interface of the tokenizer's app info (vptr only; no method is called or defined here, so the slot is not known)
class IAppInfoGetter {
public:
    virtual s32 getVariable(s32 id) const;
};

// Knife::Message::RenderTarget (only the fields the text drawing reads). The vtable pointer is at 0x00.
class RenderTarget {
public:
    void *vtbl;             // 0x00
    u8 unk_04[0x24 - 0x04];
    u8 *cellBase;           // 0x24
    s32 mode;               // 0x28: 4 and 0x0e draw OBJ text, 5 and 0x0f draw nothing, the others draw BG text
    u8 unk_2c[0x30 - 0x2c];
    s32 unk_30;             // 0x30: passed to the screen queries
    s32 unk_34;             // 0x34
    s32 unk_38;             // 0x38: first argument of the OBJ count query
    s32 unk_3c;             // 0x3c: second argument of the OBJ count query
    u8 unk_40[0x4c - 0x40];
    s32 unk_4c;             // 0x4c
    s32 unk_50;             // 0x50
    s32 unk_54;             // 0x54
    s32 unk_58;             // 0x58
    s16 unk_5c;             // 0x5c
    s16 unk_5e;             // 0x5e

    s32 getNumberOfUsingOBJ(void) const;    // 0x020a4ee0
};

// Knife::Message::TextRenderer. Two interface bases: IAppInfoGetter at +0 and ITokenAnalyzer at +4 (the tokens analyze
// through the second). The tokenizer is embedded at +0x0c.
class TextRenderer : public IAppInfoGetter, public ITokenAnalyzer {
public:
    s32 renderText(const RenderTarget *target, u32 textId, Language language);          // 0x020a5138
    s32 renderText(const RenderTarget *target, const u16 *str);                         // 0x020a5184
    s32 renderText(const RenderTarget *target, const Text *text);                       // 0x020a51c8
    s32 analyzeAllTokens(const RenderTarget *target);                                   // 0x020a5220
    s32 getNumberOfTokens(void) const;                                                  // 0x020a5340
    Token *getToken(s32 index) const;                                                   // 0x020a5354
    void resetContext(void);                                                            // 0x020a536c
    s32 countTotalLines(void);                                                          // 0x020a5384
    s32 calcCurrentLineWidth(s32 index);                                                // 0x020a5410
    s32 renderBGText(const RenderTarget *target);                                       // 0x020a55d0
    s32 renderOBJText(const RenderTarget *target);                                      // 0x020a5740
    void clearCanvas(u8 value);                                                         // 0x020a58b4

    u8 initialized;            // 0x08
    u8 unk_09[3];
    TextTokenizer tokenizer;   // 0x0c: 0x3c bytes
    void *pool;                // 0x48: memory pool of the tokenizer
    u32 poolSize;              // 0x4c
    u8 unk_50[0x10];           // 0x50
    const RenderTarget *target; // 0x60: target of the current analyze
    u32 unk_64;                // 0x64
    u32 unk_68;                // 0x68
    void *screenBuffer[8];     // 0x6c
    void **tokenList;          // 0x8c: token list when set, otherwise the tokenizer's list
    s32 tokenListCount;        // 0x90
    u8 flag94;                 // 0x94
    u8 flag95;                 // 0x95
    s32 unk_98;                // 0x98
    s32 unk_9c;                // 0x9c
    s32 unk_a0;                // 0xa0
    s32 unk_a4;                // 0xa4: cleared by resetContext
    s32 unk_a8;                // 0xa8
    s32 unk_ac;                // 0xac
    s32 unk_b0;                // 0xb0: cleared by resetContext
    s32 unk_b4;                // 0xb4: cleared by resetContext
    s32 unk_b8;                // 0xb8: cleared by resetContext
};

}
}

// Plain functions of the text renderer unit (no original C++ name in the debug build)
extern "C" s32 Knife_Message_TextRenderer_setTokenListAndAnalyze(Knife::Message::TextRenderer *self, const Knife::Message::RenderTarget *target, void **list, s32 count);
extern "C" s32 Knife_Message_TextRenderer_returnZero(void *self, const void *target);

#endif
