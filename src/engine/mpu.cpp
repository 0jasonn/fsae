#include "engine/functions.h"
#include "global.h"
#include "types.h"

extern "C" void Mpu_SetRegion0(u32 value);
extern "C" void Mpu_SetRegion1(u32 value);
extern "C" void Mpu_SetRegion2(u32 value);
extern "C" void Mpu_SetRegion3(u32 value);
extern "C" void Mpu_SetRegion4(u32 value);
extern "C" void Mpu_SetRegion5(u32 value);
extern "C" void Mpu_SetRegion6(u32 value);
extern "C" void Mpu_SetRegion7(u32 value);
extern "C" u32 Mpu_GetRegion0(void);
extern "C" u32 Mpu_GetRegion1(void);
extern "C" u32 Mpu_GetRegion2(void);
extern "C" u32 Mpu_GetRegion3(void);
extern "C" u32 Mpu_GetRegion4(void);
extern "C" u32 Mpu_GetRegion5(void);
extern "C" u32 Mpu_GetRegion6(void);
extern "C" u32 Mpu_GetRegion7(void);

// ARM946E-S protection unit region registers (CP15 c6, one register per region).
// Set writes r0 to region N, Get reads region N back.

ARM asm void Mpu_SetRegion0(u32 value) {
    mcr p15, 0, r0, c6, c0, 0
    bx lr
}

ARM asm void Mpu_SetRegion1(u32 value) {
    mcr p15, 0, r0, c6, c1, 0
    bx lr
}

ARM asm void Mpu_SetRegion2(u32 value) {
    mcr p15, 0, r0, c6, c2, 0
    bx lr
}

ARM asm void Mpu_SetRegion3(u32 value) {
    mcr p15, 0, r0, c6, c3, 0
    bx lr
}

ARM asm void Mpu_SetRegion4(u32 value) {
    mcr p15, 0, r0, c6, c4, 0
    bx lr
}

ARM asm void Mpu_SetRegion5(u32 value) {
    mcr p15, 0, r0, c6, c5, 0
    bx lr
}

ARM asm void Mpu_SetRegion6(u32 value) {
    mcr p15, 0, r0, c6, c6, 0
    bx lr
}

ARM asm void Mpu_SetRegion7(u32 value) {
    mcr p15, 0, r0, c6, c7, 0
    bx lr
}

ARM asm u32 Mpu_GetRegion0(void) {
    mrc p15, 0, r0, c6, c0, 0
    bx lr
}

ARM asm u32 Mpu_GetRegion1(void) {
    mrc p15, 0, r0, c6, c1, 0
    bx lr
}

ARM asm u32 Mpu_GetRegion2(void) {
    mrc p15, 0, r0, c6, c2, 0
    bx lr
}

ARM asm u32 Mpu_GetRegion3(void) {
    mrc p15, 0, r0, c6, c3, 0
    bx lr
}

ARM asm u32 Mpu_GetRegion4(void) {
    mrc p15, 0, r0, c6, c4, 0
    bx lr
}

ARM asm u32 Mpu_GetRegion5(void) {
    mrc p15, 0, r0, c6, c5, 0
    bx lr
}

ARM asm u32 Mpu_GetRegion6(void) {
    mrc p15, 0, r0, c6, c6, 0
    bx lr
}

ARM asm u32 Mpu_GetRegion7(void) {
    mrc p15, 0, r0, c6, c7, 0
    bx lr
}
