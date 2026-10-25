#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/codec.h"

extern "C" void Str_CopyN(u8 *dst, const u8 *src, u32 count);

// Encodes the NUL-terminated wide string src into dst, at most max bytes. Each character is encoded through the
// codec into a small temporary and copied out. The terminator is written when the source ends. Returns the number
// of bytes written.
ARM u32 Codec_WideToBytes(u8 *dst, const u16 *src, u32 max) {
    u8 temp[4];
    u32 count;
    s32 written;
    u32 wide;

    count = 0;
    if (dst == NULL || src == NULL) {
        return 0;
    }
    for (;;) {
        wide = *src;
        if (wide == 0) {
            dst[count] = 0;
            break;
        }
        src++;
        written = Codec_StoreChar(temp, wide);
        if (count + written > max) {
            break;
        }
        Str_CopyN(dst + count, temp, written);
        count += written;
        if (count > max) {
            break;
        }
    }
    return count;
}
