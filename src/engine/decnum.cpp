#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Decimal digit string: the exponent (s16) at +2, the digit count at +4 and the digits (most significant first) from +5.
typedef struct DecNum {
    u16 unk_00;
    s16 exponent;
    u8 count;
    u8 digits[1];
} DecNum;

extern "C" s32 DecNum_RoundDir(DecNum *self, u8 n);

// DecNum_RoundDir(self, n) (0x0200a41c): rounding direction for the digits after the first n. Returns 1 to round up,
// -1 to round down. A digit above 5 rounds up, below 5 down; a 5 rounds up when a nonzero digit follows, otherwise
// the rounding goes to even (up when the last kept digit is odd).
ARM s32 DecNum_RoundDir(DecNum *self, u8 n) {
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
    if (self->digits[n - 1] & 1) {
        return 1;
    }
    return -1;
}
