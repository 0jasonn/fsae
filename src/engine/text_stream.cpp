#include "engine/functions.h"
#include "global.h"

// TextStream_ReadU16 (provisional name): the halfword at the cursor; the cursor moves two bytes on.
extern "C" u16 TextStream_ReadU16(u8 *self);
ARM u16 TextStream_ReadU16(u8 *self) {
    u8 *cursor;
    u16 value;

    cursor = *(u8 **)self;
    value = *(u16 *)cursor;
    *(u8 **)self = cursor + 2;
    return value;
}

