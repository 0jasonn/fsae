#include "types.h"

// GzFile::open (0x0208dfc8): opens a file of the archive file system by path. The first call initialises the file system
// (DMA not used) and gives the WBT its packet buffer.

extern "C" {
void FS_Init(u32 dmaNo);  // proposed signature: knife_file_2.h declares it without the DMA channel argument
u32 WBT_SetPacketSize(s32 a, s32 b);
void *func_0208e148(u32 size);
void FS_InitFile(void *file);
BOOL FS_FindDir(void *file, void *path);
extern u32 data_021770a0; // set once the file system is initialised

BOOL GzFile_open(void *file, const char *path);
}

BOOL GzFile_open(void *file, const char *path) {
    s32 packetSize;

    if (data_021770a0 == 0) {
        data_021770a0 = 1;
        FS_Init(0xffffffff);
        packetSize = WBT_SetPacketSize(0, 0);
        WBT_SetPacketSize((s32)func_0208e148(packetSize), packetSize);
    }
    FS_InitFile(file);
    return FS_FindDir(file, (void *)path) != FALSE;
}
