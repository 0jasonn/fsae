#include "engine/functions.h"
#include "global.h"
#include "game/textreader.h"

// Functions in this file (original names from the debug build):
//   TextReader::cancel() (0x020a25f8), cleanup() (0x020a260c)

extern u8 data_0211ee30[]; // TextReader vtable

extern "C" void Knife_Message_TextReader_cleanup(void *self);

// TextReader::cancel() (0x020a25f8): asks the read to end, once it is in progress
extern "C" void Knife_Message_TextReader_cancel(void *self);
void Knife_Message_TextReader_cancel(void *self) {
    KnifeTextReader *reader = (KnifeTextReader *)self;

    if (reader->unk_06 != 0) {
        reader->unk_07 = 1;
    }
}

// TextReader::cleanup() (0x020a260c): clears the read state
extern "C" void Knife_Message_TextReader_cleanup(void *self);
void Knife_Message_TextReader_cleanup(void *self) {
    KnifeTextReader *reader = (KnifeTextReader *)self;

    reader->unk_04 = 0;
    reader->unk_05 = 0;
    reader->unk_06 = 0;
    reader->unk_07 = 0;
    reader->unk_08 = 0;
    reader->unk_0c = 0;
    reader->paramPtr = NULL;
    reader->paramPos = 0;
}
