#ifndef WIP_D_KMSGREADER_H
#define WIP_D_KMSGREADER_H

#include "types.h"

// Knife::Message::KMsgFileReader (vtable data_0211ad2c): reads a KMSG text file. The three pointer words after the
// vtable are cleared by finalize.
namespace Knife {
namespace Message {

class KMsgFileReader {
public:
    void finalize(void);

    void *vtbl;         // 0x00
    u8 *data;           // 0x04: the file data, NULL when not open
    u8 *body;           // 0x08: data + 0x10 (the text headers), set by initialize
    u32 size;           // 0x0c
};

}
}

extern "C" {
// Dtors of the message readers (dsd names; the D0/D1 forms are plain symbols)
void *gz_Knife_Message_KMsgFileReader_dtor_KMsgFileReader_08e1c4(void *self);
void *Knife_Message_TextTokenizer_dtor_TextTokenizer_08e3f8(void *self);
void Knife_Message_TextTokenizer_finalize(void *self);
extern char data_0211ad2c[]; // KMsgFileReader vtable
extern char data_0211af7c[]; // TextTokenizer vtable
}

#endif
