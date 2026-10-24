#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Byte search helpers used by the engine (no original names; were FindByteForward and FindByteBackward). Both return the
// address of the first (forward) or last (backward) byte equal to value within count bytes, or NULL.

extern "C" u8 *FindByteForward(const u8 *buf, int value, u32 count);
extern "C" u8 *FindByteBackward(const u8 *buf, int value, u32 count);

ARM u8 *FindByteForward(const u8 *buf, int value, u32 count) {
    u8 wanted;
    u8 byte;

    wanted = (u8)value;
    if (count != 0) {
        do {
            byte = *buf++;
            if (byte == wanted) {
                return (u8 *)(buf - 1);
            }
            count--;
        } while (count != 0);
    }
    return NULL;
}

ARM u8 *FindByteBackward(const u8 *buf, int value, u32 count) {
    u8 wanted;
    u8 byte;

    wanted = (u8)value;
    buf += count;
    if (count != 0) {
        do {
            byte = *--buf;
            if (byte == wanted) {
                return (u8 *)buf;
            }
            count--;
        } while (count != 0);
    }
    return NULL;
}
