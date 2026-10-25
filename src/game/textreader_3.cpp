#include "engine/functions.h"
#include "global.h"

// Functions in this file (original names from the debug build, or invented where marked):
//   TextReader::TextReader() (0x020a23bc, name invented: the debug build has none)

extern u8 data_0211ee30[]; // vtable of TextReader
// Knife::Message::Text members used here (the class is in engine/text_tokenizer.h, which clashes with the game headers)
namespace Knife {
namespace Message {
class Text {
public:
    void clear(void);
    u32 readFirstCharacter(u32 *out) const;
};
}
}
extern "C" void Knife_Message_TextReader_cleanup(void *self);

// TextReader::TextReader() (0x020a23bc): sets the vtable, clears the text at +0x0c and resets the reader
extern "C" void *Knife_Message_TextReader_TextReader(void *self);
ARM void *Knife_Message_TextReader_TextReader(void *self) {
    *(void **)self = data_0211ee30;
    ((Knife::Message::Text *)((u8 *)self + 0x0c))->clear();
    Knife_Message_TextReader_cleanup(self);
    return self;
}
