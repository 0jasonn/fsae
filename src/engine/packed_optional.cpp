#include "engine/functions.h"
#include "global.h"
#include "types.h"

extern "C" const u8 *func_0200b24c(const u8 *src, u32 *value);
extern "C" void Packed_ReadOptional(const u8 *src);

// Packed_ReadOptional(src) (0x0200ca58): the first byte of src holds the flags. The packed value after the two-byte header
// is read into a local; with bit 0x40 set a second packed value follows it and is read the same way.
ARM void Packed_ReadOptional(const u8 *src) {
    u32 value;
    u8 flags;
    const u8 *next;

    flags = *src;
    next = func_0200b24c(src + 2, &value);
    if (flags & 0x40) {
        func_0200b24c(next, &value);
    }
}
