#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/text_tokenizer.h"

// Knife::Message::TextTokenizer, 0x0208f29c to 0x0208f394: onReadError (the overflow slot), duplicateText (copies a text
// into the top of the pool) and cleanupTokens (calls each token's dtor, then clears the pool).

namespace Knife {
namespace Message {

// Slot 22 of the vtable (0x0208f29c): marks the tokenizer as overflowed
ARM void TextTokenizer::onReadError(void) {
    overflow = 1;
}

}
}
