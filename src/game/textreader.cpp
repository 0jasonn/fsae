#include "engine/functions.h"
#include "global.h"

// Functions in this file (original names from the debug build):
//   TextReader::~TextReader() (0x020a23e8, base, and 0x020a2408, deleting)

extern u8 data_0211ee30[]; // TextReader vtable

// Text reader state (Knife::Message::TextReader). Only the fields the functions matched so far use are named.
typedef struct KnifeTextReader {
    void *vtbl;         // 0x00
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;          // 0x06: set while a read is in progress, cancel asks for an end
    u8 unk_07;          // 0x07: set by cancel
    u8 unk_08;
    u8 unk_09[3];
    u32 unk_0c;
    u8 *paramPtr;       // 0x10: next parameter bytes
    s32 paramPos;       // 0x14: bytes of the parameters read so far
} KnifeTextReader;

extern "C" void Knife_Message_TextReader_cleanup(void *self);

// TextReader::~TextReader() (0x020a23e8): sets the vtable, cleans up and returns the object
extern "C" void *Knife_Message_TextReader_dtor_TextReader_0a23e8(void *self);
ARM void *Knife_Message_TextReader_dtor_TextReader_0a23e8(void *self) {
    KnifeTextReader *reader = (KnifeTextReader *)self;

    reader->vtbl = data_0211ee30;
    Knife_Message_TextReader_cleanup(reader);
    return reader;
}

// TextReader::~TextReader() (0x020a2408): the deleting destructor, as 0x020a23e8 and then operator delete
extern "C" void *Knife_Message_TextReader_dtor_TextReader_0a2408(void *self);
ARM void *Knife_Message_TextReader_dtor_TextReader_0a2408(void *self) {
    KnifeTextReader *reader = (KnifeTextReader *)self;

    reader->vtbl = data_0211ee30;
    Knife_Message_TextReader_cleanup(reader);
    operator delete(reader);
    return reader;
}
