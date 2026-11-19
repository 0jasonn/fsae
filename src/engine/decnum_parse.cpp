#include "engine/decnum.h"

// Read at most 32 decimal digits, preserving the original overflow-rounding tests.
extern "C" void func_0200a75c(DecNum *self, const u8 *text, s32 exponent) {
    s32 count = 0;
    u8 next;

    self->exponent = (s16)exponent;
    ((u8 *)self)[0] = 0;
    while (count < 0x20 && *text != 0) {
        self->digits[count++] = (u8)(*text++ - 0x30);
    }

    next = *text;
    self->count = (u8)count;
    if (next == 0) {
        return;
    }
    if (next < 5) {
        return;
    }
    if (next > 5) {
        goto round_up;
    }
    next = text[1];
    text++;
    while (next != 0) {
        if (next != 0x30) {
            goto round_up;
        }
        next = *++text;
    }

    {
        u32 index = count - 1;
        if ((self->digits[index] & 1) == 0) {
            return;
        }
    }
round_up:
    DecNum_Increment(self, self->count);
}
