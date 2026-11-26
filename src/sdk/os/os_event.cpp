#include "global.h"
#include "types.h"
#include "sdk/os/os_event.h"
#include "sdk/os/os_halt_api.h"

// Stops the CPU until the next interrupt (CP15 wait-for-interrupt).
asm void OS_Halt(void) {
    mov r0, #0
    mcr p15, 0, r0, c7, c0, 4
    bx lr
}

void OS_InitEvent(OsEvent *event) {
    event->queue.head = event->queue.tail = NULL;
    event->flags = 0;
}
