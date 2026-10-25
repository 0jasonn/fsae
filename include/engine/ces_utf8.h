#ifndef WIP_D_CES_UTF8_H
#define WIP_D_CES_UTF8_H

#include "types.h"
#include "engine/text_tokenizer.h"

// Knife::Message::CES_UTF8 (vtable data_0211affc): UTF-8, one to four bytes per character. The generic getLength
// (ICharacterEncodingScheme) counts the characters through readFirstCharacter. Not declared in text_tokenizer.h yet.
namespace Knife {
namespace Message {

class CES_UTF8 : public ICharacterEncodingScheme {
public:
    u32 readFirstCharacter(const void *data, u32 size, u32 *out) const;
    u32 convert(void *out, u32 outSize, s32 character) const;
};

}
}

#endif
