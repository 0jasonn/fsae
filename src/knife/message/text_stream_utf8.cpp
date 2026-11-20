#include "knife/message/text_stream_api.h"
#include "knife/message/text_stream_utf8.h"

// Reads one 1-, 2-, or 3-byte UTF-8 code point and advances the stream cursor.
extern "C" u16 TextStream_ReadUtf8(u8 *self) {
    u8 *cursor = *(u8 **)self;
    u8 first = cursor[0];
    u16 value = first;

    if ((first & 0x80) == 0) {
        *(u8 **)self = cursor + 1;
    } else if ((first & 0xe0) == 0xc0) {
        value = (u16)(((first & 0x1f) << 6) | (cursor[1] & 0x3f));
        *(u8 **)self = cursor + 2;
    } else {
        value = (u16)(((u32)(first & 0x1f) << 12) | ((cursor[1] & 0x3f) << 6) | (cursor[2] & 0x3f));
        *(u8 **)self = cursor + 3;
    }

    return value;
}
