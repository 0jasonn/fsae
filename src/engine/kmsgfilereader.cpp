#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/kmsgreader.h"

// Knife::Message::KMsgFileReader dtors, 0x0208e1c4 to 0x0208e20c. The deleting dtor frees the block.

// KMsgFileReader::~KMsgFileReader, non-deleting dtor (0x0208e1c4): sets the vtable and finalizes
extern "C" void *gz_Knife_Message_KMsgFileReader_dtor_KMsgFileReader_08e1c4(void *self);
ARM void *gz_Knife_Message_KMsgFileReader_dtor_KMsgFileReader_08e1c4(void *self) {
    *(void **)self = data_0211ad2c;
    ((Knife::Message::KMsgFileReader *)self)->finalize();
    return self;
}

// KMsgFileReader::~KMsgFileReader, deleting dtor (0x0208e1e4): as above, then frees the block
extern "C" void *gz_Knife_Message_KMsgFileReader_dtor_KMsgFileReader_08e1e4(void *self);
ARM void *gz_Knife_Message_KMsgFileReader_dtor_KMsgFileReader_08e1e4(void *self) {
    *(void **)self = data_0211ad2c;
    ((Knife::Message::KMsgFileReader *)self)->finalize();
    operator delete(self);
    return self;
}
