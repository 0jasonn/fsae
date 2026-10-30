#include "engine/functions.h"
#include "global.h"
#include "game/message_e.h"

// Functions in this file (original names from the debug build):
//   TextRenderer::countTotalLines (0x020a5384)
//   TextRenderer::calcCurrentLineWidth (0x020a5410)

namespace Knife {
namespace Message {

// TextRenderer::countTotalLines() (0x020a5384): measures every token with the analyzer (measuring mode), counting the
// line breaks into unk_a0
ARM s32 TextRenderer::countTotalLines(void) {
    s32 tokenCount = getNumberOfTokens();
    s32 i;

    resetContext();
    unk_a0 = 0;
    unk_a8 = 0;
    unk_ac = 0;
    flag94 = 1;
    flag95 = 0;
    for (i = 0; i < tokenCount; i++) {
        Token *token = getToken(i);
        token->analyze(this, 0);
    }
    unk_a0 = unk_a0 + 1;
    flag94 = 0;
    return 0;
}

// TextRenderer::calcCurrentLineWidth(int) (0x020a5410): measures the tokens from lineStart until a line break and keeps
// the widest line width in unk_ac
ARM s32 TextRenderer::calcCurrentLineWidth(s32 lineStart) {
    s32 tokenCount = getNumberOfTokens();
    s32 i;

    unk_a8 = unk_b0;
    flag94 = 0;
    flag95 = 1;
    for (i = lineStart; i < tokenCount; i++) {
        Token *token = getToken(i);
        token->analyze(this, 0);
        if (flag95 == 0) {
            break;
        }
    }
    unk_a8 = unk_a8 - unk_98;
    if (unk_a8 < 0) {
        unk_a8 = 0;
    }
    if (unk_ac < unk_a8) {
        unk_ac = unk_a8;
    }
    flag95 = 0;
    return 0;
}

}
}
