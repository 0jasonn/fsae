#include "engine/functions.h"
#include "global.h"
#include "types.h"

extern "C" u8 Bits_PopCount64(u64 x);
extern "C" s32 Fp_SignBit(f64 x);

// Number of set bits in a 64-bit value (the classic SWAR popcount), returned as a byte.
ARM u8 Bits_PopCount64(u64 x) {
    x -= (x >> 1) & 0x5555555555555555ULL;
    x = (x & 0x3333333333333333ULL) + ((x >> 2) & 0x3333333333333333ULL);
    x = (x + (x >> 4)) & 0x0f0f0f0f0f0f0f0fULL;
    x += x >> 8;
    x += x >> 16;
    x += x >> 32;
    return (u8)x;
}

// Returns 1 when the sign bit of the double is set (it is the top bit of the high word), 0 otherwise.
ARM s32 Fp_SignBit(f64 x) {
    u32 lo;
    u32 hi;

    hi = *((u32 *)&x + 1);
    return (hi & 0x80000000) != 0;
}
