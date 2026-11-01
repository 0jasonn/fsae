#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "knife/message/kmsgreader.h"
#include "knife/message/kmsgfilereader_api.h"

// KMsgFileReader base dtor (0x0208e1a4): restores the KMsgFileReader vtable, finalizes the reader and returns it.
// Kept as a plain extern "C" function (see the note in matching_tips on dtors).
extern "C" Knife::Message::KMsgFileReader *Knife_Message_KMsgFileReader_dtor_KMsgFileReader_08e1a4(Knife::Message::KMsgFileReader *self);
Knife::Message::KMsgFileReader *Knife_Message_KMsgFileReader_dtor_KMsgFileReader_08e1a4(Knife::Message::KMsgFileReader *self) {
    self->vtbl = data_0211ad2c;
    self->finalize();
    return self;
}

// Knife::Message::KMsgFileReader dtors, 0x0208e1c4 to 0x0208e20c. The deleting dtor frees the block.

// KMsgFileReader::~KMsgFileReader, non-deleting dtor (0x0208e1c4): sets the vtable and finalizes
extern "C" void *gz_Knife_Message_KMsgFileReader_dtor_KMsgFileReader_08e1c4(void *self);
void *gz_Knife_Message_KMsgFileReader_dtor_KMsgFileReader_08e1c4(void *self) {
    *(void **)self = data_0211ad2c;
    ((Knife::Message::KMsgFileReader *)self)->finalize();
    return self;
}

// KMsgFileReader::~KMsgFileReader, deleting dtor (0x0208e1e4): as above, then frees the block
void *gz_Knife_Message_KMsgFileReader_dtor_KMsgFileReader_08e1e4(void *self) {
    *(void **)self = data_0211ad2c;
    ((Knife::Message::KMsgFileReader *)self)->finalize();
    operator delete(self);
    return self;
}
