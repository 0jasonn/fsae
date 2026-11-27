#include "global.h"
#include "types.h"
#include "sdk/fatfs/fatfs.h"
#include "engine/functions.h"
#include "sdk/pxi/pxi_fifo.h"
#include "sdk/card/card.h"
#include "sdk/os/dc_cache.h"
#include "sdk/os/os_interrupts.h"
#include "sdk/fatfs/stdconv_table_wrap_api.h"

void FATFSi_SyncInitialization(u32 arg) {
    FatfsRequest *request;

    request = FATFSi_AllocateCommandBuffer(0x80000000);
    request->arg.io.handle = 0;
    request->arg.io.value = 0;
    request->arg.io.length = arg;
    StdConv_GetUnicodeTable(&request->arg.io.handle, &request->arg.io.value);
    Fatfs_SendToPxi(request);
    FATFSi_WaitForRequest(request);
    FATFSi_FreeCommandBuffer(request);
}
