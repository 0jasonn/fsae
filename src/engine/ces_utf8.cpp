#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/ces_utf8.h"

// Knife::Message::CES_UTF8::convert (0x02090164) and readFirstCharacter (0x02090290): UTF-8 encoding of one character
// (1 to 4 bytes, the ranges are the code points below 0x80, 0x800, 0x10000 and 0x200000) and decoding of the first one.

namespace Knife {
namespace Message {

// CES_UTF8::convert(void*, unsigned long, int) const (0x02090164): writes the character, FALSE (0) when the output is
// NULL, the character is out of range or the buffer is too small; otherwise the number of bytes written
ARM u32 CES_UTF8::convert(void *out, u32 outSize, s32 character) const {
    u8 *bytes;

    if (out == NULL) {
        return 0;
    }
    bytes = (u8 *)out;
    if (character >= 0 && character < 0x80) {
        if (outSize < 1) {
            return 0;
        }
        bytes[0] = (u8)character;
        return 1;
    }
    if (character >= 0x80 && character < 0x800) {
        if (outSize < 2) {
            return 0;
        }
        bytes[0] = (u8)(((character & 0x7c0) >> 6) | 0xc0);
        bytes[1] = (u8)((character & 0x3f) | 0x80);
        return 2;
    }
    if (character >= 0x800 && character < 0x10000) {
        if (outSize < 3) {
            return 0;
        }
        bytes[0] = (u8)(((character & 0xf000) >> 12) | 0xe0);
        bytes[1] = (u8)(((character & 0xfc0) >> 6) | 0x80);
        bytes[2] = (u8)((character & 0x3f) | 0x80);
        return 3;
    }
    if (character >= 0x10000 && character < 0x200000) {
        if (outSize < 4) {
            return 0;
        }
        bytes[0] = (u8)(((character & 0x1c0000) >> 18) | 0xf0);
        bytes[1] = (u8)(((character & 0x3f000) >> 12) | 0x80);
        bytes[2] = (u8)(((character & 0xfc0) >> 6) | 0x80);
        bytes[3] = (u8)((character & 0x3f) | 0x80);
        return 4;
    }
    return 0;
}

// CES_UTF8::readFirstCharacter(void const*, unsigned long, unsigned long*) const (0x02090290): the code point of the
// first character and its length in *out (0 when there is none)
ARM u32 CES_UTF8::readFirstCharacter(const void *data, u32 size, u32 *out) const {
    const u8 *bytes;
    u32 local;

    if (out == NULL) {
        out = &local;
    }
    *out = 0;
    if (data == NULL) {
        return 0;
    }
    bytes = (const u8 *)data;
    if (size >= 1 && bytes[0] < 0x80) {
        *out = 1;
        return bytes[0];
    }
    if (size >= 2 && (bytes[0] & 0xe0) == 0xc0) {
        *out = 2;
        return ((bytes[0] & 0x1f) << 6) | (bytes[1] & 0x3f);
    }
    if (size >= 3 && (bytes[0] & 0xf0) == 0xe0) {
        *out = 3;
        return ((bytes[0] & 0x0f) << 12) | ((bytes[1] & 0x3f) << 6) | (bytes[2] & 0x3f);
    }
    if (size >= 4 && (bytes[0] & 0xf8) == 0xf0) {
        *out = 4;
        return ((bytes[0] & 0x07) << 18) | ((bytes[1] & 0x3f) << 12) | ((bytes[2] & 0x3f) << 6) | (bytes[3] & 0x3f);
    }
    return 0;
}

}
}
