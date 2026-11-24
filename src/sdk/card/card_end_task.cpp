#include "engine/functions.h"
#include "sdk/card/card_task.h"

void CARDi_EndTask(CardTaskWork *work) {
    void (*completion)(void *) = work->completion;
    void *completionArg = work->completionArg;
    u32 irqState = OS_DisableInterrupts();

    work->flags &= ~0x4c;
    OS_WakeupThread(work->waitQueue);
    OS_RestoreInterrupts(irqState);

    if (completion != NULL) {
        completion(completionArg);
    }
}
