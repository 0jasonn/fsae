#include "engine/functions.h"
#include "global.h"

// Functions in this file (original names from the debug build):
//   TextReader::cancel() (0x020a25f8), cleanup() (0x020a260c)

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

// TextReader::cancel() (0x020a25f8): asks the read to end, once it is in progress
extern "C" void Knife_Message_TextReader_cancel(void *self);
ARM void Knife_Message_TextReader_cancel(void *self) {
    KnifeTextReader *reader = (KnifeTextReader *)self;

    if (reader->unk_06 != 0) {
        reader->unk_07 = 1;
    }
}

// TextReader::cleanup() (0x020a260c): clears the read state
extern "C" void Knife_Message_TextReader_cleanup(void *self);
ARM void Knife_Message_TextReader_cleanup(void *self) {
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
