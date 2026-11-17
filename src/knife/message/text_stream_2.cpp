#include "engine/functions.h"
#include "global.h"
#include "knife/message/text_stream_api.h"

// Read a Shift-JIS character and advance by the encoded length.
u16 TextStream_ReadSjis(u8 *self) {
    u8 *cursor = *(u8 **)self;
    u8 lead = cursor[0];
    u16 value;

    if (lead < 0x81) {
        goto check_high_lead;
    }
    if (lead < 0xa0) {
        goto read_pair;
    }
check_high_lead:
    if (lead < 0xe0) {
        goto read_byte;
    }
read_pair:
    value = (u16)((lead << 8) | cursor[1]);
    *(u8 **)self += 2;
    goto done;
read_byte:
    *(u8 **)self += 1;
    value = lead;
done:
    return value;
}

// TextStream_ReadU8 (provisional name): the byte at the cursor; the cursor moves one byte on.
u8 TextStream_ReadU8(u8 *self) {
    u8 *cursor;
    u8 value;

    cursor = *(u8 **)self;
    value = *cursor;
    *(u8 **)self = cursor + 1;
    return value;
}
