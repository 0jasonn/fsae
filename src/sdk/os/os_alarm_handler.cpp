#include "sdk/os/os_alarm.h"

// Timer interrupt handler: runs OSi_ArrangeTimer (hand-written ARM in the SDK).
asm void OSi_AlarmHandler(void) {
    nofralloc
    stmdb sp!, {r0, lr}
    bl OSi_ArrangeTimer
    ldmia sp!, {r0, lr}
    bx lr
}
