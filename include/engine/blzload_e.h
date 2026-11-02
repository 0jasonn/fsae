#ifndef WIP_E_BLZLOAD_E_H
#define WIP_E_BLZLOAD_E_H

#include "types.h"

// NitroSDK FSFile (0x48 bytes), opaque here
typedef struct BlzFile {
    u8 unk_00[0x48];
} BlzFile;

extern "C" {
void FS_InitFile(void *file);
BOOL FS_FindDir(void *file, void *path);
u32 Fs_GetFileLengthWrap(void *file);
BOOL FS_SeekFile(void *file, s32 offset, s32 origin);
s32 FS_ReadFile(void *file, void *buffer, s32 size);
void FS_CloseFile(void *file);
s32 MI_SecureUncompressBLZ(void *data, u32 compressedSize, u32 uncompressedSize);
void *func_020c2c34(void *heap, s32 size);
void Heap_VirtualFree(void *heap, void *block);

}

#endif
