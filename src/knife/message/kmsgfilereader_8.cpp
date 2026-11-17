#include "engine/functions.h"
#include "knife/message/kmsgreader.h"

// Knife::Message::KMsgFileReader::initialize (0x0208e20c): accepts a KMSG header with version 1.
BOOL Knife_Message_KMsgFileReader_initialize(void *self, const void *data, u32 size) {
    Knife::Message::KMsgFileReader *reader;
    u8 *fileData;

    reader = (Knife::Message::KMsgFileReader *)self;
    fileData = (u8 *)data;
    reader->finalize();
    if (fileData == NULL || size < 0x10) {
        return FALSE;
    }
    reader->data = fileData;
    reader->body = fileData + 0x10;
    reader->size = size;
    if (*(u32 *)reader->data != 0x47534d4b) { // "KMSG"
        reader->finalize();
        return FALSE;
    }
    if (*(u16 *)(reader->data + 4) != 1 || *(u16 *)(reader->data + 6) != 0) {
        reader->finalize();
        return FALSE;
    }
    return TRUE;
}
