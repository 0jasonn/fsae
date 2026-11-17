#include "engine/functions.h"
#include "engine/decnum.h"

// DecNum_RoundDir(self, n) (0x0200a41c): rounding direction for the digits after the first n. Returns 1 to round up,
// -1 to round down. A digit above 5 rounds up, below 5 down; a 5 rounds up when a nonzero digit follows, otherwise
// the rounding goes to even (up when the last kept digit is odd).
s32 DecNum_RoundDir(DecNum *self, s32 n) {
    u8 *p;
    u8 *end;

    p = self->digits + n;
    if (self->digits[n] > 5) {
        return 1;
    }
    if (self->digits[n] < 5) {
        return -1;
    }
    p++;
    end = self->digits + self->count;
    while (p < end) {
        if (*p != 0) {
            return 1;
        }
        p++;
    }
    // Keep the index subtraction separate from the digit field offset.
    u32 prevDigitAddr = (u32)self + (u32)(n - 1) + 5;
    if (*(const u8 *)prevDigitAddr & 1) {
        return 1;
    }
    return -1;
}
