#include "sdk/card/card_task.h"

// Finishes a DMA read after checking for card removal and refreshing the ROM interface.
void CARDi_DmaReadDone(void) {
    CardTaskWork *work;

    CARDi_CheckPulledOutCore(CARDi_ReadRomIDCore());
    CARDi_RefreshRom(8);
    work = (CardTaskWork *)&data_0217dae0;
    *(u32 *)work->commandArea = 0;
    CARDi_EndTask(work);
}
