#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/text_tokenizer.h"

// Knife::Message::Text, 0x0208f9c8 to 0x0208fb00 (the convert function follows): clear, the string constructor, set,
// readFirstCharacter, readFirstCharacterAndStep and getLength. A Text is {character encoding scheme, data, size in bytes}.

extern "C" s32 func_0200a3ac(const u16 *str); // wcslen (dsd name), returns the number of characters

namespace Knife {
namespace Message {

// Text::clear (0x0208f9c8): the default state, no scheme, no data
ARM void Text::clear(void) {
    ces = NULL;
    data = NULL;
    size = 0;
}

// Text::Text(unsigned short const*) (0x0208f9dc): a UTF-16LE text, the size is the length in bytes
}
}

ARM Knife::Message::Text *Knife_Message_Text_Text(Knife::Message::Text *self, const u16 *str) {
    self->ces = (Knife::Message::ICharacterEncodingScheme *)data_021770b4;
    self->data = str;
    self->size = func_0200a3ac(str) << 1;
    return self;
}

namespace Knife {
namespace Message {

// Text::set(ICharacterEncodingScheme*, void const*, unsigned long) (0x0208fa0c)
ARM void Text::set(ICharacterEncodingScheme *newCes, const void *newData, u32 newSize) {
    ces = newCes;
    data = newData;
    size = newSize;
}

// Text::readFirstCharacter(unsigned long*) const (0x0208fa14): 0 when the text is empty; the scheme reads the character
ARM u32 Text::readFirstCharacter(u32 *out) const {
    u32 local;

    if (data == NULL || ces == NULL) {
        return 0;
    }
    if (out == NULL) {
        out = &local;
    }
    return ces->readFirstCharacter(data, size, out);
}

// Text::readFirstCharacterAndStep(unsigned long*) (0x0208fa54): reads the first character and moves the start past it
ARM u32 Text::readFirstCharacterAndStep(u32 *out) {
    u32 local;
    u32 result;

    if (data == NULL || ces == NULL) {
        return 0;
    }
    if (out == NULL) {
        out = &local;
    }
    result = ces->readFirstCharacter(data, size, out);
    if (*out == 0) {
        return 0;
    }
    data = (const u8 *)data + *out;
    size = size - *out;
    return result;
}

// Text::getLength() const (0x0208fac0): the length of the text in characters, 0 when empty
ARM u32 Text::getLength(void) const {
    if (data == NULL || ces == NULL) {
        return 0;
    }
    return ces->getLength(data, size);
}

}
}
