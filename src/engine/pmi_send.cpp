#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/wip_a_decls.h"

// Starts sending a block of words over PXI: fails with 1 while a send is busy, otherwise marks the send busy, saves the
// three parameters, sends each word and returns 0 with interrupts restored.
extern "C" s32 PMi_StartSendBlock(u32 *words, s32 count, u32 a, u32 b, u32 c);

ARM s32 PMi_StartSendBlock(u32 *words, s32 count, u32 a, u32 b, u32 c) {
    u32 irqState;
    s32 i;

    irqState = OS_DisableInterrupts();
    if (data_0212b920.busy != 0) {
        OS_RestoreInterrupts(irqState);
        return 1;
    }
    data_0212b920.busy = 1;
    data_0212b920.param3c = a;
    data_0212b920.param34 = b;
    data_0212b920.param38 = c;
    for (i = 0; i < count; i++) {
        PMi_SendPxiData(words[i]);
    }
    OS_RestoreInterrupts(irqState);
    return 0;
}
