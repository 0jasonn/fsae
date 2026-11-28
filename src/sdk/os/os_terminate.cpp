#include "global.h"
#include "types.h"
#include "sdk/os/os_terminate.h"
#include "sdk/os/os_interrupts.h"
#include "sdk/os/os_halt_api.h"
#include "sdk/os/os_sync_pxi.h"
#include "sdk/fatfs/engine_word_api.h"
#include "sdk/fatfs/fatfs.h"

void OS_Terminate(void) {
    void (*callback)(void *);
    u16 imeValue;

    callback = data_02129cc0.callback;
    if (callback != NULL) {
        data_02129cc0.callback = NULL;
        callback(data_02129cc0.callbackArg);
    }
    if (data_02129cc0.terminating == 0) {
        data_02129cc0.terminating = 1;
        if (OS_GetProcMode() != 0x12) {
            imeValue = *(volatile u16 *)0x04000208;
            *(volatile u16 *)0x04000208 = 1;
            OS_EnableInterrupts();
        }
        if (Engine_ReadWordA() != 0) {
            FATFS_UnmountAll();
        }
        OSi_SendToPxi(0x20);
    }
    Os_DisableIrqAndHalt();
}
