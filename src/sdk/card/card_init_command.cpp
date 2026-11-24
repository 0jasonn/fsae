#include "engine/functions.h"
#include "sdk/card/card.h"
#include "sdk/os/dc_cache.h"
#include "sdk/card/card_task.h"

void CARDi_InitCommand(void) {
    u8 *commandArea = data_0217da80;
    CardTaskWork *resource = (CardTaskWork *)&data_0217dae0;
    u32 size = 0x60;

    resource->commandArea = commandArea;
    MIi_CpuClearFast(0, commandArea, size);
    DC_FlushRange(commandArea, size);
    PXI_SetFifoRecvCallback(0xb, CARDi_OnFifoRecv);
}
