#include "engine/functions.h"
#include "global.h"
#include "game/message_e.h"

// Functions in this file (original names from the debug build, plus one plain helper):
//   TextRenderer::renderText x3 (0x020a5138, 0x020a5184, 0x020a51c8), setTokenListAndAnalyze (0x020a520c, plain name),
//   TextRenderer::analyzeAllTokens (0x020a5220)

namespace Knife {
namespace Message {

// TextRenderer::renderText(RenderTarget const*, unsigned long, Language) (0x020a5138): tokenizes the message id and
// analyzes the tokens
ARM s32 TextRenderer::renderText(const RenderTarget *target, u32 textId, Language language) {
    s32 result = 0;

    tokenList = NULL;
    tokenListCount = 0;
    if (tokenizer.tokenize(textId, language, this)) {
        result = analyzeAllTokens(target);
    }
    return result;
}

// TextRenderer::renderText(RenderTarget const*, unsigned short const*) (0x020a5184): tokenizes a string and analyzes it
ARM s32 TextRenderer::renderText(const RenderTarget *target, const u16 *str) {
    s32 result = 0;

    tokenList = NULL;
    tokenListCount = 0;
    if (tokenizer.tokenize(str)) {
        result = analyzeAllTokens(target);
    }
    return result;
}

// TextRenderer::renderText(RenderTarget const*, Text const*) (0x020a51c8): tokenizes a Text and analyzes it
ARM s32 TextRenderer::renderText(const RenderTarget *target, const Text *text) {
    s32 result = 0;

    tokenList = NULL;
    tokenListCount = 0;
    if (tokenizer.tokenize(text)) {
        result = analyzeAllTokens(target);
    }
    return result;
}

}
}

// Knife_Message_TextRenderer_setTokenListAndAnalyze (0x020a520c): stores an explicit token list and count, then analyzes (tail call)
ARM s32 Knife_Message_TextRenderer_setTokenListAndAnalyze(Knife::Message::TextRenderer *self,
                                                           const Knife::Message::RenderTarget *target, void **list,
                                                           s32 count) {
    self->tokenList = list;
    self->tokenListCount = count;
    return self->analyzeAllTokens(target);
}

namespace Knife {
namespace Message {

namespace Knife {
namespace Message {

// TextRenderer::analyzeAllTokens(RenderTarget const*) (0x020a5220): resets the layout, analyzes every token and draws
// the text as the target mode asks
ARM s32 TextRenderer::analyzeAllTokens(const RenderTarget *newTarget) {
    s32 lastLine = -1;
    s32 count;
    s32 i;

    target = newTarget;
    clearCanvas(0);
    countTotalLines();
    count = getNumberOfTokens();
    resetContext();
    unk_ac = 0;
    unk_b0 = newTarget->unk_5c;
    unk_b4 = newTarget->unk_5e;
    if (count > 0) {
        for (i = 0; i < count; i++) {
            if (lastLine != unk_a4) {
                lastLine = unk_a4;
                calcCurrentLineWidth(i);
            }
            Token *token = getToken(i);
            token->analyze(this, 0);
        }
    }
    target = NULL;
    switch (newTarget->mode) {
    case 4:
    case 14:
        return renderOBJText(newTarget);
    case 5:
    case 15:
        return Knife_Message_TextRenderer_returnZero(this, newTarget);
    default:
        return renderBGText(newTarget);
    }

}
}
}
}
}
