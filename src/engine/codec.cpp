#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/codec.h"

// Dispatches one character conversion through the codec record (data_020df74c[2]).
ARM s32 Codec_ConvertChar(u16 *wide, const u8 *src, u32 count) {
    return data_020df74c[2]->convert(wide, src, count);
}

// Single-byte codec: NULL source returns 0, zero count returns -1, otherwise the byte is widened into *wide
// (when wide is set) and the result is 1 for a non-zero byte.
ARM s32 Codec_ByteToWide(u16 *wide, const u8 *src, u32 count) {
    if (src == NULL) {
        return 0;
    }
    if (count == 0) {
        return -1;
    }
    if (wide != NULL) {
        *wide = *src;
    }
    if (*src == 0) {
        return 0;
    }
    return 1;
}
