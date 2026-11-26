#include "global.h"
#include "types.h"
#include "sdk/fx/fx.h"

// Hand-written assembly in the SDK: writes a 2x2 identity matrix (1.0 in 20.12 fixed point).

asm void MTX_Identity22_(MtxFx22 *mtx) {
    mov r1, #0
    mov r2, #0x1000
    mov r3, #0
    stmia r0!, {r2, r3}
    stmia r0!, {r1, r2}
    bx lr
}
