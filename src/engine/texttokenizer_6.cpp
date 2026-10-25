#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/text_tokenizer.h"

// Knife::Message::TextTokenizer::cleanupTokens (0x0208f32c)

namespace Knife {
namespace Message {

// TextTokenizer::cleanupTokens() (0x0208f32c): calls the complete dtor (slot 0) of each token, then clears the pool and
// empties the token list. Does nothing when there is no pool.
ARM void TextTokenizer::cleanupTokens(void) {
    s32 i;

    if (poolBase == NULL) {
        return;
    }
    for (i = 0; i < tokenCount; i++) {
        tokens[i]->dtorSlot();
    }
    Mem_Set(poolBase, 0, poolSize);
    poolUsed = 0;
    tokenCount = 0;
}

}
}
