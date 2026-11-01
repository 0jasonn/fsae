#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/decnum.h"

// Keeps the first `keep` digits of a decimal string, rounding half to even on the first dropped digit (the rounding
// direction is worked out inline, like DecNum_RoundDir). Trailing zeros are dropped; a carry out of the first digit
// makes the number 1 with the exponent raised. A negative `keep`, or no digits kept, gives zero.
void DecNum_RoundDigits(DecNum *self, s32 keep) {
    u8 *digits;
    u8 *first;
    u8 *end;
    s32 roundUp;
    s32 carry;
    u8 digit;

    if (keep < 0) {
    zero:
        self->count = 1;
        self->exponent = 0;
        self->digits[0] = '0';
        return;
    }
    if (keep >= self->count) {
        return;
    }
    digits = self->digits;
    first = digits + keep + 1;
    digit = (u8)(*--first - '0');
    if (digit == 5) {
        end = digits + self->count;
        for (;;) {
            end--;
            if (end <= first) {
                break;
            }
            if (*end != '0') {
                break;
            }
        }
        if (end == first) {
            roundUp = first[-1] & 1;
        } else {
            roundUp = 1;
        }
    } else {
        roundUp = digit > 5;
    }

    carry = roundUp;
    while (keep != 0) {
        u8 value;
        u8 *slot;

        slot = first - 1;
        value = (u8)(*slot - '0' + carry);
        carry = (value > 9);
        if (carry || value == 0) {
            keep--;
            first = slot;
        } else {
            *slot = value + '0';
            break;
        }
    }

    if (carry != 0) {
        self->count = 1;
        self->exponent++;
        self->digits[0] = '1';
        return;
    }
    if (keep == 0) {
        goto zero;
    }
    self->count = (u8)keep;
}
