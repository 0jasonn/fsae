#ifndef SDK_FS_FS_ROM_H
#define SDK_FS_FS_ROM_H

// TwlSDK FS ROM archive: the card ROM callbacks and the ROM FAT archive procedures.
#include "types.h"
#include "sdk/fs/fs_file.h"
#include "sdk/fs/fs_archive.h"

// data_021297b8: the DMA channel handed to the card ROM read and the ROM bank value passed (as u16) to the CARD and
// G3C lock calls.
typedef struct FsRomState {
    u32 dmaNo;                          // 0x00
    u32 value;                          // 0x04
} FsRomState;

extern FsRomState data_021297b8;

extern "C" {
void FSi_OnRomReadDone(FSArchive *arc);
s32 FSi_ReadRomCallback(FSArchive *arc, void *dst, u32 src, u32 length);
s32 FSi_ROMFAT_GetArchiveCaps(FSArchive *arc, u32 *caps);
s32 FSi_ROMFAT_CloseDirectory(FSArchive *arc, FSFile *file);
s32 FSi_ROMFAT_GetFileLength(FSArchive *arc, FSFile *file, u32 *length);
s32 FSi_ROMFAT_GetFilePosition(FSArchive *arc, FSFile *file, u32 *position);
s32 FSi_ROMFAT_CloseFile(FSArchive *arc, FSFile *file);
s32 FSi_ROMFAT_Activate(FSArchive *arc);
s32 FSi_ROMFAT_Idle(FSArchive *arc);
s32 FSi_ROMFAT_Suspend(FSArchive *arc);
s32 FSi_ROMFAT_Resume(FSArchive *arc);
s32 FSi_ROMFAT_ReadFile(FSArchive *arc, FSFile *file, void *buffer, u32 *length);
s32 FSi_ROMFAT_WriteFile(FSArchive *arc, FSFile *file, const void *source, u32 *length);
s32 FSi_ROMFAT_GetPath(FSArchive *arc, FSFile *file, void *id, void *buffer, u32 *length);
s32 FSi_ROMFAT_OpenFileFast(FSArchive *arc, FSFile *file, u32 id);

// Not decompiled yet.
s32 FSi_IsUnreadableRomOffset(FSArchive *arc, u32 offset); // compares the archive name; offset (r1) is not used
void FSi_InitRomArchive(u32 dmaNo);
}

#endif
