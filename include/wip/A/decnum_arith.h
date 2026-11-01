#ifndef WIP_A_DECNUM_ARITH_H
#define WIP_A_DECNUM_ARITH_H

// Decimal digit string arithmetic (layout: include/engine/decnum.h). Declared here until the reviewer moves them.
#include "types.h"
#include "engine/decnum.h"

extern "C" {
void DecNum_Multiply(DecNum *out, const DecNum *a, const DecNum *b);
void func_0200a488(DecNum *self, u8 n);
}

#endif
