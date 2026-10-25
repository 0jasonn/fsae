#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/text_tokenizer.h"

// Knife::Message::ICharacterEncodingScheme and the default scheme table, 0x0208fb94 to 0x0208fc84: the generic getLength
// (counts the characters through readFirstCharacter), getDefaultCES and the two getters of the static schemes.

namespace Knife {
namespace Message {

// ICharacterEncodingScheme::getLength(void const*, unsigned long) const (0x0208fb94): counts the characters of the data
ARM u32 ICharacterEncodingScheme::getLength(const void *data, u32 size) const {
    u32 consumed;
    u32 count;
    u32 next;

    if (data == NULL) {
        return 0;
    }
    count = 0;
    next = readFirstCharacter(data, size, &consumed);
    while (next != 0) {
        data = (const u8 *)data + consumed;
        size -= consumed;
        count += 1;
        next = readFirstCharacter(data, size, &consumed);
    }
    return count;
}

// getDefaultCES(Language) (0x0208fc14): copies the table and returns the scheme of the language, NULL outside 0 to 9
ARM const ICharacterEncodingScheme *getDefaultCES(Language language) {
    CESTable table;

    table = data_0211b050;
    if (language < 0 || language >= 10) {
        return NULL;
    }
    return table.entries[language];
}

}
}

// Getter of the static scheme at data_021770b4 (0x0208fc6c)
extern "C" void *Knife_Message_getCESObject_021770b4(void);
ARM void *Knife_Message_getCESObject_021770b4(void) {
    return data_021770b4;
}

// Getter of the static scheme at data_021770b8 (0x0208fc78)
extern "C" void *Knife_Message_getCESObject_021770b8(void);
ARM void *Knife_Message_getCESObject_021770b8(void) {
    return data_021770b8;
}
