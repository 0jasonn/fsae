#include "engine/functions.h"
#include "engine/callees.h"
#include "global.h"
#include "types.h"

// Os_DisableIrqAndHalt() (0x02019e54): disables interrupts and halts the CPU for good (OS_Halt in a loop).
extern "C" void Os_DisableIrqAndHalt(void);

ARM void Os_DisableIrqAndHalt(void) {
    OS_DisableInterrupts();
    for (;;) {
        OS_Halt();
    }
}
