#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/text_tokenizer.h"

// Knife::Message::CES_UTF32LE, 0x0208ffbc to 0x0209003c: one 32-bit word per character. convert stores the word,
// getCharCount is the size in words, readFirstCharacter reads the first word.

namespace Knife {
namespace Message {

// CES_UTF32LE::convert(void*, unsigned long, int) const (0x0208ffbc)
ARM u32 CES_UTF32LE::convert(void *out, u32 outSize, s32 character) const {
    if (out == NULL) {
        return 0;
    }
    if (outSize < 4) {
        return 0;
    }
    *(u32 *)out = (u32)character;
    return 1;
}

// CES_UTF32LE::getCharCount(void const*, unsigned long) const (0x0208ffdc, vtable slot 3)
ARM u32 CES_UTF32LE::getCharCount(const void *data, u32 size) const {
    if (data == NULL) {
        return 0;
    }
    return size >> 2;
}

// CES_UTF32LE::readFirstCharacter(void const*, unsigned long, unsigned long*) const (0x0208ffec)
ARM u32 CES_UTF32LE::readFirstCharacter(const void *data, u32 size, u32 *out) const {
    u32 local;

    if (out == NULL) {
        out = &local;
    }
    *out = 0;
    if (data == NULL || size < 4) {
        return 0;
    }
    *out = 4;
    return *(const u32 *)data;
}

// CES_UTF16LE::convert(void*, unsigned long, int) const (0x0209003c): one unit for the characters below 0x10000, a
// surrogate pair above
ARM u32 CES_UTF16LE::convert(void *out, u32 outSize, s32 character) const {
    u16 *units;
    s32 plane;

    if (out == NULL) {
        return 0;
    }
    if (character >= 0 && character < 0x10000) {
        if (outSize < 2) {
            return 0;
        }
        *(u16 *)out = (u16)character;
        return 2;
    }
    if (outSize < 4) {
        return 0;
    }
    units = (u16 *)out;
    plane = ((character & 0x1f0000) >> 16) - 1;
    units[0] = (u16)(0xd800 | (plane << 6) | ((character & 0xfc00) >> 10));
    units[1] = (u16)(0xdc00 | (character & 0x3ff));
    return 4;
}

}
}
