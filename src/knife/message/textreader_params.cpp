#include "engine/functions.h"
#include "global.h"
#include "knife/message/text_tokenizer.h"
#include "knife/message/message_classes.h"
#include "knife/message/textreader_readparam.h"

// TODO(headers): declared in knife/message/textreader_param.h, which this file cannot include (its types clash with the
// ones used here); see the header restructure report.
extern "C" void Knife_Message_TextReader_readParam_Str(void *self, void *out);
// Functions in this file (plain names from the debug build, C linkage; the first argument is the TextReader):
//   Knife_Message_TextReader_readParams (0x020a2978)

// TextReader::readParams(TagFormat, TextReader::Param*) (0x020a2978): reads the parameters of a tag as the format
// asks (0: none, 1: a u16, 2: a text, 3: a u16 and two texts); any other format sets the error flag at +5
extern "C" void Knife_Message_TextReader_readParams(void *self, s32 format, s32 *params) {
    switch (format) {
    case 0:
        break;
    case 1:
        params[0] = Knife_Message_TextReader_readParam_U16(self);
        break;
    case 2:
        Knife_Message_TextReader_readParam_Str(self, params + 1);
        break;
    case 3:
        params[0] = Knife_Message_TextReader_readParam_U16(self);
        Knife_Message_TextReader_readParam_Str(self, params + 5);
        Knife_Message_TextReader_readParam_Str(self, params + 9);
        break;
    default:
        ((u8 *)self)[5] = 1;
        break;
    }
}
