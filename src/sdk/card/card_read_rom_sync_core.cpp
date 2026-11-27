#include "sdk/card/card_task.h"

// Calls the configured ROM reader with the work item's destination, address, and size.
void CARDi_ReadRomSyncCore(CardTaskWork *work) {
    CardTaskWork *cardWork;

    data_0217e004.readFunction(0, work->destination, work->romAddress, work->transferSize);
    CARDi_CheckPulledOutCore(CARDi_ReadRomIDCore());
    CARDi_RefreshRom(8);
    cardWork = (CardTaskWork *)&data_0217dae0;
    *(u32 *)cardWork->commandArea = 0;
}
