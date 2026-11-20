#include "engine/functions.h"
#include "engine/droprupees.h"
#include "global.h"

// DropRupees (0x02050504): drops the given rupee amount as few objects as possible: value-20 rupees first, then
// value-5 and value-1 ones, each in a random direction (Random() & 0x1f).
void DropRupees(u8 type, u16 amount) {
    s16 count = amount / 20;
    amount = amount % 20;
    while (count-- != 0) {
        DropRupeeDir(type, 20, Random() & 0x1f);
    }
    count = amount / 5;
    while (count-- != 0) {
        DropRupeeDir(type, 5, Random() & 0x1f);
    }
    count = amount % 5;
    while (count-- != 0) {
        DropRupeeDir(type, 1, Random() & 0x1f);
    }
}
