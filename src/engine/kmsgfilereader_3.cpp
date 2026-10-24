#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/kmsgreader.h"

// KMsgFileReader base dtor (0x0208e1a4): restores the KMsgFileReader vtable, finalizes the reader and returns it.
// Kept as a plain extern "C" function (see the note in matching_tips on dtors).
extern "C" Knife::Message::KMsgFileReader *Knife_Message_KMsgFileReader_dtor_KMsgFileReader_08e1a4(Knife::Message::KMsgFileReader *self);
ARM Knife::Message::KMsgFileReader *Knife_Message_KMsgFileReader_dtor_KMsgFileReader_08e1a4(Knife::Message::KMsgFileReader *self) {
    self->vtbl = data_0211ad2c;
    self->finalize();
    return self;
}
