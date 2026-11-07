#include "engine/functions.h"
#include "global.h"

// Functions in this file (original names from the debug build):
//   Knife::Message::TextReader::readParam_U16() (0x020a29e8)

// Reader state of the tag parameters (the layout is the one of textreader.cpp)
typedef struct KnifeTextReaderParams {
    void *vtbl;         // 0x00
    u8 unk_04;
    u8 failed;          // 0x05: set once a read ran past the end of the parameters
    u8 unk_06[0x10 - 0x06];
    u8 *paramPtr;       // 0x10: next parameter bytes
    u32 paramPos;       // 0x14: bytes of the parameters read so far
} KnifeTextReaderParams;

// TextReader::readParam_U16() (0x020a29e8): reads the next 16-bit parameter, or 0 and failed once none is left
extern "C" u16 Knife_Message_TextReader_readParam_U16(void *a) {
    KnifeTextReaderParams *reader = (KnifeTextReaderParams *)a;
    u16 value;

    if (reader->paramPos < 2 || reader->failed != 0) {
        reader->failed = 1;
        return 0;
    }
    value = *(u16 *)reader->paramPtr;
    reader->paramPtr += 2;
    reader->paramPos = reader->paramPos + 2;
    return value;
}
