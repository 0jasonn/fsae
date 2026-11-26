#ifndef SDK_FS_FS_ARCHIVE_H
#define SDK_FS_FS_ARCHIVE_H

// TwlSDK FS archive (FSArchive, 0x5c bytes) and the archive functions. Only the fields the matched code touches are
// named; offsets are from the ROM.
#include "types.h"

struct FSArchive;
typedef s32 (*FSArchiveAccessFunc)(struct FSArchive *arc, void *buffer, u32 offset, u32 length);

// Table the archive points at (FS_MountArchive's second argument): the memory base of the archive image and the access
// callbacks.
typedef struct FSArchiveContext {
    u32 base;                           // 0x00
    u32 unk_04[7];                      // 0x04
    FSArchiveAccessFunc read;           // 0x20
    FSArchiveAccessFunc write;          // 0x24
} FSArchiveContext;

typedef struct FSArchive {
    union {
        s8 ptr[4];
        const char *longName;
    } name;                             // 0x00
    u8 unk_04[8];
    u32 unk_0c;                         // 0x0c
    u32 unk_10;                         // 0x10
    u32 flag;                           // 0x14: bit 1 mounted, bit 2 tables loaded
    u8 unk_18[8];
    FSArchiveContext *context;          // 0x20
    const void *vtbl;                   // 0x24: archive interface (data_020c90fc for the ROM FAT archive)
    u8 unk_28[0x2c];
    void *proc;                         // 0x54
    u32 procFlags;                      // 0x58
} FSArchive; // 0x5c bytes

extern FSArchive data_021297c0;         // the ROM archive

extern "C" {
u32 FS_GetArchiveBase(FSArchive *arc);
u32 FS_GetArchiveOffset(FSArchive *arc, u32 offset);
const char *FS_GetArchiveName(FSArchive *arc);
s32 FS_IsArchiveTableLoaded(FSArchive *arc);
void FS_InitArchive(FSArchive *arc);
s32 FS_MountArchive(FSArchive *arc, FSArchiveContext *context, const void *vtbl);
void FS_SetArchiveProc(FSArchive *arc, void *proc, u32 flags);
s32 FSi_ReadMemCallback(FSArchive *arc, void *dst, u32 offset, u32 length);
s32 FSi_WriteMemCallback(FSArchive *arc, const void *src, u32 offset, u32 length);

// Not decompiled yet.
u32 FS_LoadArchiveTables(FSArchive *arc, void *mem, u32 size);
s32 FS_NotifyArchiveAsyncEnd(FSArchive *arc, u32 result);
}

#endif
