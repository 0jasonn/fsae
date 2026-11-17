#ifndef WIP_A_DECNUM_H
#define WIP_A_DECNUM_H

// Decimal digit string used by the float formatting code.
#include "types.h"

typedef struct DecNum {
    u16 unk_00;
    s16 exponent;      // 0x02
    u8 count;          // 0x04: number of digits
    u8 digits[1];      // 0x05: digits, most significant first
} DecNum;

extern "C" {
s32 DecNum_RoundDir(DecNum *self, s32 keep);
void DecNum_Increment(DecNum *self, s32 keep);
void DecNum_Truncate(DecNum *self, s32 keep);
void DecNum_RoundDigits(DecNum *self, s32 keep);
void DecNum_RoundDigits2(DecNum *self, s32 keep);
}

#endif
