#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/text_tokenizer.h"

// Knife::Message::CES_ISO8859_1 and CES_ASCII, 0x02090398 to 0x020904b0: convert writes one byte, readFirstCharacter reads
// one byte, getLength is the byte count (0 without data). The ASCII reader returns the byte sign-extended.

namespace Knife {
namespace Message {

// CES_ISO8859_1::convert(void*, unsigned long, int) const (0x02090398)
ARM u32 CES_ISO8859_1::convert(void *out, u32 outSize, s32 character) const {
    if (out == NULL) {
        return 0;
    }
    if ((u32)character >= 0x100) {
        return 0;
    }
    if (outSize < 1) {
        return 0;
    }
    *(u8 *)out = (u8)character;
    return 1;
}

// CES_ISO8859_1::getCharCount(void const*, unsigned long) const (0x020903c4, vtable slot 3): one character per byte
ARM u32 CES_ISO8859_1::getCharCount(const void *data, u32 size) const {
    if (data == NULL) {
        return 0;
    }
    return size;
}

// CES_ISO8859_1::readFirstCharacter(void const*, unsigned long, unsigned long*) const (0x020903d4)
ARM u32 CES_ISO8859_1::readFirstCharacter(const void *data, u32 size, u32 *out) const {
    u32 local;

    if (out == NULL) {
        out = &local;
    }
    *out = 0;
    if (data == NULL || size < 1) {
        return 0;
    }
    *out = 1;
    return *(const u8 *)data;
}

// CES_ASCII::convert(void*, unsigned long, int) const (0x02090424)
ARM u32 CES_ASCII::convert(void *out, u32 outSize, s32 character) const {
    if (out == NULL) {
        return 0;
    }
    if ((u32)character >= 0x80) {
        return 0;
    }
    if (outSize < 1) {
        return 0;
    }
    *(u8 *)out = (u8)character;
    return 1;
}

// CES_ASCII::getCharCount(void const*, unsigned long) const (0x02090450, vtable slot 3)
ARM u32 CES_ASCII::getCharCount(const void *data, u32 size) const {
    if (data == NULL) {
        return 0;
    }
    return size;
}

// CES_ASCII::readFirstCharacter(void const*, unsigned long, unsigned long*) const (0x02090460)
ARM u32 CES_ASCII::readFirstCharacter(const void *data, u32 size, u32 *out) const {
    u32 local;

    if (out == NULL) {
        out = &local;
    }
    *out = 0;
    if (data == NULL || size < 1) {
        return 0;
    }
    *out = 1;
    return *(const s8 *)data;
}

}
}
