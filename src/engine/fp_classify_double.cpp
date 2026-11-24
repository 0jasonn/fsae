#include "types.h"

// Classify IEEE-754 bits: NaN=1, infinity=2, zero=3, normal=4, subnormal=5.
extern "C" s32 func_02005bcc(f64 value);
s32 func_02005bcc(f64 value) {
    u32 high = ((const u32 *)&value)[1];
    u32 exponent = high & 0x7ff00000;

    if (exponent == 0) {
        goto zeroExponent;
    }
    if (exponent != 0x7ff00000) {
        goto normal;
    }
    if ((high & 0x000fffff) != 0 || ((const u32 *)&value)[0] != 0) {
        return 1;
    }
    return 2;

zeroExponent:
    if ((high & 0x000fffff) != 0 || ((const u32 *)&value)[0] != 0) {
        return 5;
    }
    return 3;

normal:
    return 4;
}
