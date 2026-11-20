#include "types.h"

// Provisional ring-buffer view. Split each write at the 0x100-row boundary.
extern "C" void func_020bc43c(void *owner, const s16 *pos, void (*writeSpan)(void *, s32, s32));
void func_020bc43c(void *owner, const s16 *pos, void (*writeSpan)(void *, s32, s32)) {
    u8 *self = (u8 *)owner;
    s16 start = *(s16 *)(self + 0x1c);
    s16 end = *(s16 *)(self + 0x20);
    s16 limit = *(s16 *)(self + 0x22);
    s16 lo;
    s16 hi;
    s32 mask;
    s32 index;
    s32 width;
    s32 span;

    if (end <= start) {
        hi = start + pos[1];
        s16 clippedEnd = end + pos[1];
        if (limit <= clippedEnd) {
            clippedEnd = limit;
        }
        lo = start + pos[0];
        if (clippedEnd <= lo) {
            clippedEnd = lo;
        }
        lo = clippedEnd;
    } else {
        lo = start + pos[0];
        hi = end + pos[0];
    }

    width = (s16)(hi - lo);
    mask = *(s16 *)(self + 0x16) - 1;
    index = lo & mask;
    if (width <= 0) {
        return;
    }
    do {
        span = 0x100 - (index & 0xff);
        if (width <= span) {
            span = width;
        }
        writeSpan(*(u8 **)(self + 0x10) + ((index * *(s16 *)(self + 0x14)) * 2),
                  (index & 0xff) << 9, span << 9);
        width -= span;
        index = (index + span) & mask;
    } while (width > 0);
}
