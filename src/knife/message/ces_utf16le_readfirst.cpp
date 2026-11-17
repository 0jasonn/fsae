#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "knife/message/text_tokenizer.h"

namespace Knife {
namespace Message {

// CES_UTF16LE::readFirstCharacter(void const*, unsigned long, unsigned long*) const (0x020900b4): reads one UTF-16 unit,
// or a surrogate pair. Stores the number of bytes read in *out (0 when nothing valid was read) and returns the character.
u32 CES_UTF16LE::readFirstCharacter(const void *data, u32 size, u32 *out) const {
    u32 skipped;
    const u16 *units;
    int highUnit;
    int lowUnit;
    int plane;
    int middleByte;

    if (out == NULL) {
        out = &skipped;
    }
    *out = 0;
    if (data == NULL) {
        return 0;
    }
    if (size < 2) {
        return 0;
    }
    units = (const u16 *)data;
    highUnit = units[0];
    if ((highUnit & 0xfc00) == 0xd800) {
        if (size < 4) {
            return 0;
        }
        lowUnit = units[1];
        if ((lowUnit & 0xfc00) != 0xdc00) {
            return 0;
        }
        *out = 4;
        plane = ((highUnit & 0x3c0) >> 6) + 1;
        middleByte = ((highUnit & 0x3f) << 2) | ((lowUnit & 0x300) >> 8);
        return (plane << 16) | (middleByte << 8) | (lowUnit & 0xff);
    }
    *out = 2;
    return highUnit;
}

}
}
