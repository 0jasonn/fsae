#include "engine/decnum.h"

extern "C" void func_0200ab78(DecNum *out, f64 value);

// Convert, round to the requested precision, then encode the digits as characters.
extern "C" void func_0200acf8(const DecNumFormat *format, f64 value, DecNum *out) {
    s32 precision = format->precision;
    s32 i;

    func_0200ab78(out, value);
    if (out->digits[0] > 9) {
        return;
    }
    if (precision > 0x20) {
        precision = 0x20;
    }
    DecNum_Truncate(out, precision);
    while (out->count < precision) {
        out->digits[out->count++] = 0;
    }
    out->exponent -= (s16)(out->count - 1);
    i = 0;
    if ((s32)out->count <= 0) {
        return;
    }
    do {
        out->digits[i] += 0x30;
        i++;
    } while (i < out->count);
}
