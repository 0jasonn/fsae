#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/kmsgreader.h"

// Knife::Message::KMsgFileReader::findLocalizedTextByTextID (0x0208e2a8): finds the header of a text id and converts it
// to the localized text. Returns FALSE when the header is missing or the output is NULL.
extern "C" BOOL Knife_Message_KMsgFileReader_findLocalizedTextByTextID(Knife::Message::KMsgFileReader *self, u32 textId, void *out);
extern "C" void *Knife_Message_KMsgFileReader_findTextHeaderByTextID(Knife::Message::KMsgFileReader *self, u32 textId);
extern "C" void Knife_Message_KMsgFileReader_convertTextHeaderToLocalizedText(Knife::Message::KMsgFileReader *self, void *out, void *header);
ARM BOOL Knife_Message_KMsgFileReader_findLocalizedTextByTextID(Knife::Message::KMsgFileReader *self, u32 textId, void *out) {
    void *header;

    header = Knife_Message_KMsgFileReader_findTextHeaderByTextID(self, textId);
    if (header == NULL || out == NULL) {
        return FALSE;
    }
    Knife_Message_KMsgFileReader_convertTextHeaderToLocalizedText(self, out, header);
    return TRUE;
}
