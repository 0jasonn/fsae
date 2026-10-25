#include "engine/functions.h"
#include "engine/callees.h"
#include "global.h"
#include "types.h"

// Os_IrqDisabledFlush() (0x02017b68): runs func_02017650 with interrupts disabled.
extern "C" void Os_IrqDisabledFlush(void);
extern "C" void func_02017650(void);

ARM void Os_IrqDisabledFlush(void) {
    u32 state;

    state = OS_DisableInterrupts();
    func_02017650();
    OS_RestoreInterrupts(state);
}
