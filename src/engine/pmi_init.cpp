#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/pmi_send.h"

extern "C" void Engine_Relay0201a070(void);
extern "C" s32 PXI_IsCallbackReady(u32 fifo, u32 kind);
extern "C" void PXI_SetFifoRecvCallback(u32 fifo, void (*callback)(u32, u32, s32));
extern "C" void WaitByLoop(u32 count);
extern "C" void func_0201c958(u32 tag, u32 data, s32 err);
extern "C" void PMi_InitSend(void);

// PMi_InitSend() (0x0201c8b8): once only (the ready flag is 0), clears the busy flag and the parameter, calls
// Engine_Relay0201a070, waits until the PXI callback for fifo 8 is ready, installs func_0201c958 as the receive
// callback and copies the word at 0x02fffc3c into the two saved fields.
void PMi_InitSend(void) {
    if (data_0212b920.ready != 0) {
        return;
    }
    data_0212b920.ready = 1;
    data_0212b920.busy = 0;
    data_0212b920.param34 = 0;
    *(u32 *)0x02fff684 = 0;
    Engine_Relay0201a070();
    if (PXI_IsCallbackReady(8, 1) == 0) {
        do {
            WaitByLoop(100);
        } while (PXI_IsCallbackReady(8, 1) == 0);
    }
    PXI_SetFifoRecvCallback(8, func_0201c958);
    {
        u32 word = *(u32 *)0x02fffc3c;

        data_0212b920.unk_10 = word;
        data_0212b920.unk_0c = word;
    }
}
