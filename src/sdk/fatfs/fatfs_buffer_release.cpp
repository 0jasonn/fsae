#include "global.h"
#include "types.h"
#include "sdk/fatfs/fatfs.h"
#include "engine/functions.h"
#include "sdk/pxi/pxi_fifo.h"
#include "sdk/card/card.h"
#include "sdk/os/dc_cache.h"
#include "sdk/os/os_interrupts.h"

FatfsRequest *FATFSi_AllocateEmergencyCommandBuffer(u32 command) {
    FatfsRequest *request;

    if (OS_GetProcMode() != 0x12) {
        return FATFSi_AllocateCommandBuffer(command);
    }
    request = data_021277e0.emergencyBuffer;
    request->command = command;
    request->result = 2;
    request->next = NULL;
    request->flags = 0;
    return request;
}

void FATFSi_FreeCommandBuffer(FatfsRequest *request) {
    if (request == data_021277e0.commandBuffer) {
        OS_UnlockMutex(&data_021277e0.mutex);
    }
}
