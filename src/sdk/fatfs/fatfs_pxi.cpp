#include "global.h"
#include "types.h"
#include "sdk/fatfs/fatfs.h"
#include "engine/functions.h"
#include "sdk/pxi/pxi_fifo.h"
#include "sdk/card/card.h"
#include "sdk/os/dc_cache.h"
#include "sdk/os/os_interrupts.h"

void FATFSi_SendToPXI(FatfsRequest *request) {
    DC_FlushRange(request, 0x800);
    while (PXI_SendWordByFifo(0x14, (u32)request >> 5, 0) < 0) {
    }
}

void FATFSi_PXICallback(u32 tag, u32 data, s32 err) {
    u32 address;

    address = data << 5;
    if (address < 0x2000000) {
        CARDi_NotifyEvent(address >> 5, 0);
    } else {
        FATFSi_NotifyRequestCompletion((FatfsRequest *)address);
    }
}
