#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "knife/message/text_tokenizer.h"
#include "knife/message/texttags.h"
#include "knife/message/value_token.h"

namespace Knife {
namespace Message {

void TextTokenizer::onReadTextSETag(Voice voice) {
    u8 *token = NULL;

    if (allocValueToken(this, data_0211ae3c, &token)) {
        *(s32 *)(token + 4) = voice;
        return;
    }
    Knife_Message_TextReader_cancel(textReader);
    overflow = 1;
}

void TextTokenizer::onReadPictTag(Pictogram pictogram) {
    u8 *token = NULL;

    if (allocValueToken(this, data_0211ae5c, &token)) {
        *(s32 *)(token + 4) = pictogram;
        return;
    }
    Knife_Message_TextReader_cancel(textReader);
    overflow = 1;
}

}
}
