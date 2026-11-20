#include "engine/functions.h"
#include "sdk/callees.h"
#include "global.h"
#include "types.h"
#include "sdk/os/os_halt_api.h"

// Os_DisableIrqAndHalt() (0x02019e54): disables interrupts and halts the CPU for good (OS_Halt in a loop).

void Os_DisableIrqAndHalt(void) {
    OS_DisableInterrupts();
    for (;;) {
        OS_Halt();
    }
}
