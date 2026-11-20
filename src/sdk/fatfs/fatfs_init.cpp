#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/a_extern.h"

// One-time FATFS initialisation, guarded by the flag word at data_02128920. The IME register (0x04000208) is
// cleared while the interrupt state is saved and restored; a zero IME or a saved state of 0x80 aborts through
// OS_Terminate. Then the request is set up, the block at data_020dfb40 is invalidated and synchronised, and the
// flag is set.

// 0x0200e578
void Fatfs_InitOnce(void) {
    volatile u16 *ime;
    u16 savedIme;
    u32 irqState;
    if (data_02128920 != 0) {
        return;
    }
    ime = (volatile u16 *)0x4000208;
    savedIme = *ime;
    *ime = 0;
    irqState = OS_DisableInterrupts();
    OS_RestoreInterrupts(irqState);
    (void)*ime;
    *ime = savedIme;
    if (savedIme == 0 || irqState == 0x80) {
        OS_Terminate();
    }
    FATFSi_InitRequest();
    DC_InvalidateRange((void *)data_020dfb40, 4);
    FATFSi_SyncInitialization(data_020dfb40);
    data_02128920 = 1;
}
