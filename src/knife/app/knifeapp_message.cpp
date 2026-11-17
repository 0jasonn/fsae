#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "knife/message/text_tokenizer.h"

using namespace Knife::Message;

extern "C" {
s32 KnifeApp_getCurrentLanguage(void *app);
void KnifeApp_MessageRequest(void *self, s32 textId, void *tokenizer, void *analyzer, s32 value);
}
extern u8 data_0211ed80[]; // vtable of the app info getter used for the request

// KnifeApp::MessageRequest (0x0208dea0): tokenizes the message, then lets each token analyze itself. Tokens with no
// parts analyze once with index 0; the others analyze each part from the first index up to their count.
void KnifeApp_MessageRequest(void *self, s32 textId, void *tokenizer, void *analyzer, s32 value) {
    struct {
        void *vtbl;
        s32 zero;
        s32 value;
    } info;
    TextTokenizer *text = (TextTokenizer *)tokenizer;
    s32 language;
    s32 i;
    s32 j;
    Token *token;

    info.vtbl = data_0211ed80;
    info.zero = 0;
    info.value = value;
    language = KnifeApp_getCurrentLanguage(KnifeApp_getInstance());
    text->tokenize(textId, (Language)language, (const IAppInfoGetter *)&info);
    for (i = 0; i < text->tokenCount; i++) {
        token = text->tokens[i];
        if (token->getCount() != 0) {
            for (j = 0; j < token->getCount(); j++) {
                token->analyze((ITokenAnalyzer *)analyzer, j);
            }
        } else {
            token->analyze((ITokenAnalyzer *)analyzer, 0);
        }
    }
}
