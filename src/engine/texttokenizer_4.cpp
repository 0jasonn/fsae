#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/texttokenize.h"

// Knife::Message::TextTokenizer::tokenize(unsigned long, Language, IAppInfoGetter const*) (0x0208e4e0): clears the
// localized texts, finds the text of the id and reads its data for the language into this tokenizer with a TextReader.
// FALSE when the id or the language has no text, or when the reader fails; otherwise TRUE unless the pool overflowed.

namespace Knife {
namespace Message {

// TextTokenizer::tokenize(unsigned long, Language, IAppInfoGetter const*) (0x0208e4e0)
ARM BOOL TextTokenizer::tokenize(u32 textId, Language language, const IAppInfoGetter *appInfo) {
    u32 reader[6]; // the TextReader (0x18 bytes, plain functions below)
    LocalizedText localized;
    Text *end;
    Text *cur;
    Text *langText;
    BOOL readOk;
    BOOL result;

    cleanupTokens();
    cur = localized.texts;
    end = localized.texts + 10;
    do {
        cur->clear();
        cur++;
    } while (cur < end);
    if (!Knife_Message_KMsgFileReader_findLocalizedTextByTextID(&msgFile, textId, &localized)) {
        return 0;
    }
    langText = &localized.texts[language];
    if (langText->data == NULL) {
        return 0;
    }
    this->textId = textId;
    this->language = language;
    this->appInfo = appInfo;
    Knife_Message_TextReader_TextReader(reader);
    readOk = Knife_Message_TextReader_readData(reader, langText, this);
    this->appInfo = NULL;
    if (readOk == 0) {
        Knife_Message_TextReader_dtor_TextReader_0a23e8(reader);
        return 0;
    }
    result = (overflow == 0);
    Knife_Message_TextReader_dtor_TextReader_0a23e8(reader);
    return result;
}

}
}
