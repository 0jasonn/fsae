#include "engine/functions.h"
#include "sdk/card/card_task.h"

void CARDi_OnFifoRecv(u32 fifo, u32 data, s32 error) {
    if (fifo != 11) {
        return;
    }
    if (error == 0) {
        return;
    }
    data_0217dae0.flags &= ~0x20;
    OS_WakeupThreadDirect((OsThread *)data_0217dae0.waitingThread);
}
