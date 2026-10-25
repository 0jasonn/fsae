#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Fp_CopySign(x, y) (0x0200ada4): x with the sign of y. The high word keeps x's exponent and mantissa bits and takes
// the sign bit of y.
extern "C" f64 Fp_CopySign(f64 x, f64 y);

ARM f64 Fp_CopySign(f64 x, f64 y) {
    *((u32 *)&x + 1) = (*((u32 *)&x + 1) & 0x7fffffff) | (*((u32 *)&y + 1) & 0x80000000);
    return x;
}

// Fp_Abs(x) (0x0200adcc): x with its sign bit cleared.
extern "C" f64 Fp_Abs(f64 x);

ARM f64 Fp_Abs(f64 x) {
    u32 *xhi = (u32 *)&x + 1;

    *xhi &= 0x7fffffff;
    return x;
}
