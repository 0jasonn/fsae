#ifndef ENGINE_DECNUM_H
#define ENGINE_DECNUM_H

// Decimal digit string used by the float formatting code.
#include "types.h"

typedef struct DecNum {
    u16 unk_00;
    s16 exponent;      // 0x02
    u8 count;          // 0x04: number of digits
    u8 digits[1];      // 0x05: digits, most significant first
} DecNum;

// Formatting options: only the signed precision at +0x02 is recovered here.
typedef struct DecNumFormat {
    u8 unk_00[2];
    s16 precision;
} DecNumFormat;

extern "C" {
void func_0200a75c(DecNum *self, const u8 *text, s32 exponent);
void func_0200acf8(const DecNumFormat *format, f64 value, DecNum *out);
s32 DecNum_RoundDir(DecNum *self, s32 keep);
void DecNum_Increment(DecNum *self, s32 keep);
void DecNum_Truncate(DecNum *self, s32 keep);
void DecNum_RoundDigits(DecNum *self, s32 keep);
void DecNum_RoundDigits2(DecNum *self, s32 keep);
}

#endif
