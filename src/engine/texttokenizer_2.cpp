#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/kmsgreader.h"

extern "C" Knife::Message::KMsgFileReader *Knife_Message_KMsgFileReader_dtor_KMsgFileReader_08e1a4(Knife::Message::KMsgFileReader *self);

// Knife::Message::KMsgFileReader::offsetToAddress (0x0208e3a0): the address of an offset in the file data (0 gives NULL)
extern "C" void *Knife_Message_KMsgFileReader_offsetToAddress(Knife::Message::KMsgFileReader *self, u32 offset);
ARM void *Knife_Message_KMsgFileReader_offsetToAddress(Knife::Message::KMsgFileReader *self, u32 offset) {
    if (offset == 0) {
        return NULL;
    }
    return (u8 *)self->data + offset;
}

// TextTokenizer ctor (0x0208e3b4): sets the vtable, constructs the embedded reader at +0x04, clears the buffers at
// +0x14 to +0x24 and finalizes the tokenizer. Kept as a plain extern "C" function.
extern "C" void *Knife_Message_TextTokenizer_ctor_08e3b4(void *self);
ARM void *Knife_Message_TextTokenizer_ctor_08e3b4(void *self) {
    u8 *tokenizer;

    tokenizer = (u8 *)self;
    *(void **)tokenizer = data_0211af7c;
    Knife_Message_KMsgFileReader_dtor_KMsgFileReader_08e1a4((Knife::Message::KMsgFileReader *)(tokenizer + 0x4));
    *(u32 *)(tokenizer + 0x14) = 0;
    *(u32 *)(tokenizer + 0x18) = 0;
    *(u32 *)(tokenizer + 0x1c) = 0;
    *(u32 *)(tokenizer + 0x20) = 0;
    *(u32 *)(tokenizer + 0x24) = 0;
    Knife_Message_TextTokenizer_finalize(self);
    return self;
}
