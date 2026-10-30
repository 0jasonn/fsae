#include "engine/functions.h"
#include "global.h"

// TextStream_ReadU8 (provisional name): the byte at the cursor; the cursor moves one byte on.
extern "C" u8 TextStream_ReadU8(u8 *self);
ARM u8 TextStream_ReadU8(u8 *self) {
    u8 *cursor;
    u8 value;

    cursor = *(u8 **)self;
    value = *cursor;
    *(u8 **)self = cursor + 1;
    return value;
}
