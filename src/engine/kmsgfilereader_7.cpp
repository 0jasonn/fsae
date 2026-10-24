#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/kmsgreader.h"

// Knife::Message::KMsgFileReader::convertTextHeaderToLocalizedText (0x0208e2dc): copies the id of a text header and, for
// each of its ten language entries, the default character encoding, the data address and the size.
extern "C" void *Knife_Message_getDefaultCES(s32 language);
extern "C" void *Knife_Message_KMsgFileReader_offsetToAddress(Knife::Message::KMsgFileReader *self, u32 offset);
extern "C" void Knife_Message_KMsgFileReader_convertTextHeaderToLocalizedText(Knife::Message::KMsgFileReader *self, void *dst, const void *header);
ARM void Knife_Message_KMsgFileReader_convertTextHeaderToLocalizedText(Knife::Message::KMsgFileReader *self, void *dst, const void *header) {
    s32 i;
    u8 *out;
    const u8 *in;
    u8 *entry;

    out = (u8 *)dst;
    in = (const u8 *)header;
    *(u32 *)out = *(const u32 *)in;
    for (i = 0; i < 10; i++) {
        entry = out + i * 12;
        *(void **)(entry + 0x4) = Knife_Message_getDefaultCES(i);
        *(void **)(entry + 0x8) = Knife_Message_KMsgFileReader_offsetToAddress(self, ((const u32 *)in)[i * 2 + 1]);
        *(u32 *)(entry + 0xc) = ((const u32 *)in)[i * 2 + 2];
    }
}
