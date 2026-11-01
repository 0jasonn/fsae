#include "engine/functions.h"
#include "global.h"
#include "game/textreader_api.h"
#include "game/textreader.h"

// Functions in this file (original names from the debug build):
//   TextReader::~TextReader() (0x020a23e8, base, and 0x020a2408, deleting)

extern u8 data_0211ee30[]; // TextReader vtable

extern "C" void Knife_Message_TextReader_cleanup(void *self);

// TextReader::~TextReader() (0x020a23e8): sets the vtable, cleans up and returns the object
extern "C" void *Knife_Message_TextReader_dtor_TextReader_0a23e8(void *self);
void *Knife_Message_TextReader_dtor_TextReader_0a23e8(void *self) {
    KnifeTextReader *reader = (KnifeTextReader *)self;

    reader->vtbl = data_0211ee30;
    Knife_Message_TextReader_cleanup(reader);
    return reader;
}

// TextReader::~TextReader() (0x020a2408): the deleting destructor, as 0x020a23e8 and then operator delete
void *Knife_Message_TextReader_dtor_TextReader_0a2408(void *self) {
    KnifeTextReader *reader = (KnifeTextReader *)self;

    reader->vtbl = data_0211ee30;
    Knife_Message_TextReader_cleanup(reader);
    operator delete(reader);
    return reader;
}
