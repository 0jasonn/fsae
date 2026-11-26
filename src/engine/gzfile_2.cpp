#include "types.h"
#include "sdk/fs/fs_file.h"
#include "sdk/fs/fs_api.h"

// GzFile::open (0x0208dfc8): opens a file of the archive file system by path. The first call initialises the file system
// (DMA not used) and gives the WBT its packet buffer.

extern "C" {
void *func_0208e148(u32 size);
extern u32 data_021770a0; // set once the file system is initialised

BOOL GzFile_open(void *file, const char *path);
}

BOOL GzFile_open(void *file, const char *path) {
    s32 packetSize;

    if (data_021770a0 == 0) {
        data_021770a0 = 1;
        FS_Init(0xffffffff);
        packetSize = WBT_SetPacketSize(0, 0);
        WBT_SetPacketSize(func_0208e148(packetSize), packetSize);
    }
    FS_InitFile((FSFile *)file);
    return FS_FindDir((FSFile *)file, path) != FALSE;
}
