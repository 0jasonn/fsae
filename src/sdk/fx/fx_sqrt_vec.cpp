#include "global.h"
#include "types.h"
#include "sdk/fx/fx.h"

s32 FX_Sqrt(s32 value) {
    if (value <= 0) {
        return 0;
    }
    *(volatile u16 *)0x40002b0 = 1;
    *(volatile u64 *)0x40002b8 = (u64)value << 32;
    return FX_GetSqrtResult();
}

s32 FX_GetSqrtResult(void) {
    while (*(volatile u16 *)0x40002b0 & 0x8000) {
    }
    return (*(volatile u32 *)0x40002b4 + 0x200) >> 10;
}

void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab) {
    ab->x = a->x + b->x;
    ab->y = a->y + b->y;
    ab->z = a->z + b->z;
}
