#include "global.h"
#include "types.h"
#include "sdk/fs/fs_api.h"
#include "sdk/fs/fs_archive.h"
#include "sdk/fs/fs_rom.h"

// Loads the file tables of the ROM archive (tail call into FS_LoadArchiveTables). The symbol name is a dsd guess.
u32 WBT_SetPacketSize(void *mem, u32 size) {
    return FS_LoadArchiveTables(&data_021297c0, mem, size);
}

void FS_Init(u32 dmaNo) {
    if (data_0212981c.fsInitialised != 0) {
        return;
    }
    data_0212981c.fsInitialised = 1;
    FS_InitFatDriver();
    FSi_InitRomArchive(dmaNo);
    FSi_InitOverlay();
}
