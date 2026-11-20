#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "knife/message/text_tokenizer.h"
#include "knife/message/texttags.h"
#include "knife/message/value_token.h"

namespace Knife {
namespace Message {

void TextTokenizer::onReadNextTag(u32 value) {
    u8 *token = NULL;

    if (allocValueToken(this, data_0211adfc, &token)) {
        *(s32 *)(token + 4) = value;
        return;
    }
    Knife_Message_TextReader_cancel(textReader);
    overflow = 1;
}

}
}
