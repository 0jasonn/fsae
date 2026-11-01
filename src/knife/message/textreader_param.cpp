#include "engine/functions.h"
#include "knife/message/textreader.h"
#include "knife/message/textreader_param.h"

// Functions in this file (plain names from the debug build, C linkage):
//   Knife_Message_TextReader_readParam_Str (0x020a2a2c)

// TextReader::readParam_Str(Text*) (0x020a2a2c): the text is the CES of the reader and the bytes from the parameter
// pointer. The reader embeds a Text at +0x0c (ces, data at +0x10 = paramPtr, size at +0x14 = paramPos); the characters
// are read through Text::readFirstCharacterAndStep. Code 0x7f ends the parameter, a zero code ends the text.
void Knife_Message_TextReader_readParam_Str(void *self, void *out) {
    KnifeTextReader *reader = (KnifeTextReader *)self;
    Knife::Message::Text *text = (Knife::Message::Text *)out;
    Knife::Message::Text *source = (Knife::Message::Text *)&reader->unk_0c;
    u32 length;
    u32 code;

    if (reader->unk_05 != 0) {
        text->ces = NULL;
        text->data = NULL;
        text->size = 0;
        return;
    }
    text->ces = (Knife::Message::ICharacterEncodingScheme *)Knife_Message_getCESObject_021770b4();
    text->data = reader->paramPtr;
    text->size = 0;
    for (;;) {
        code = source->readFirstCharacterAndStep(&length);
        if (code == 0x7f) {
            reader->unk_05 = 1;
            text->ces = NULL;
            text->data = NULL;
            text->size = 0;
            return;
        }
        if (code != 0) {
            text->size += length;
            continue;
        }
        if (((u32)reader->paramPtr & 1) == 0) {
            return;
        }
        if (reader->paramPos != 0) {
            reader->paramPtr = reader->paramPtr + 1;
            reader->paramPos -= 1;
            return;
        }
        reader->unk_05 = 1;
        text->ces = NULL;
        text->data = NULL;
        text->size = 0;
        return;
    }
}
