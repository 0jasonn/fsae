#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/kmsgreader.h"

// Knife::Message::TextTokenizer dtors, 0x0208e3f8 to 0x0208e450. The tokenizer's finalize runs first, then the
// KMsgFileReader at +0x04 is destroyed. The deleting dtor frees the block.

// TextTokenizer::~TextTokenizer, non-deleting dtor (0x0208e3f8)
extern "C" void *Knife_Message_TextTokenizer_dtor_TextTokenizer_08e3f8(void *self);
ARM void *Knife_Message_TextTokenizer_dtor_TextTokenizer_08e3f8(void *self) {
    *(void **)self = data_0211af7c;
    Knife_Message_TextTokenizer_finalize(self);
    gz_Knife_Message_KMsgFileReader_dtor_KMsgFileReader_08e1c4((u8 *)self + 0x4);
    return self;
}

// TextTokenizer::~TextTokenizer, deleting dtor (0x0208e420): as above, then frees the block
extern "C" void *Knife_Message_TextTokenizer_dtor_TextTokenizer_08e420(void *self);
ARM void *Knife_Message_TextTokenizer_dtor_TextTokenizer_08e420(void *self) {
    *(void **)self = data_0211af7c;
    Knife_Message_TextTokenizer_finalize(self);
    gz_Knife_Message_KMsgFileReader_dtor_KMsgFileReader_08e1c4((u8 *)self + 0x4);
    operator delete(self);
    return self;
}
