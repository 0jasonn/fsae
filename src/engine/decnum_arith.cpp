#include "engine/functions.h"
#include "engine/decnum.h"

// Truncates to n digits, rounding according to DecNum_RoundDir.
void DecNum_Truncate(DecNum *self, s32 n) {
    s32 direction;

    if (n <= 0) {
        return;
    }
    if (n >= self->count) {
        return;
    }
    direction = DecNum_RoundDir(self, n);
    self->count = n;
    if (direction < 0) {
        return;
    }
    DecNum_Increment(self, n);
}
