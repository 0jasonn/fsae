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

// The part of the card ROM header the archive setup reads (CARD_GetOwnRomHeader).
typedef struct FsCardHeaderTables {
    u8 unk_00[0x40];                    // 0x00
    u32 fntOffset;                      // 0x40: file name table
    u32 fntSize;                        // 0x44
    u32 fatOffset;                      // 0x48: file allocation table
    u32 fatSize;                        // 0x4c
} FsCardHeaderTables;

// Directory entry the ROM FAT ReadDirectory command fills in (the FSDirectoryEntryInfo of the SDK).
typedef struct FsDirectoryEntryInfo {
    u8 shortName[0x10];                 // 0x00
    u32 shortNameLength;                // 0x10
    char longName[0x104];               // 0x14
    u32 longNameLength;                 // 0x118
    u32 attributes;                     // 0x11c: 0x100 directory, 0x400 not readable
    u32 dates[6];                       // 0x120
    u32 unk_138[6];                     // 0x138: cleared
    u8 unk_150[0x18];                   // 0x150
    u32 fileSize;                       // 0x168
    u32 id;                             // 0x16c
} FsDirectoryEntryInfo;

// What the ROM FAT archive reads out of its tables: the archive and the table offset to read next.
typedef struct FsTableReader {
    FSArchive *arc;                     // 0x00
    u32 offset;                         // 0x04
} FsTableReader;

// Output of FSi_ROMFAT_GetPathInfo (the FSPathInfo of the SDK, 0x54 bytes).
typedef struct FsPathInfo {
    u32 attributes;                     // 0x00: 0x100 directory, 0x200 always set, 0x400 not readable
    u8 unk_04[0x48];                    // 0x04
    u32 fileSize;                       // 0x4c
    u32 id;                             // 0x50
} FsPathInfo; // 0x54 bytes

// Output of FSi_ROMFAT_GetArchiveResource (the FSArchiveResource of the SDK, 0x30 bytes).
typedef struct FsArchiveResource {
    u32 totalSize;                      // 0x00: the ROM size from the card header (offset 0x80)
    u32 unk_04[3];                      // 0x04
    u32 maxSize;                        // 0x10: 0x7fffffff
    u32 unk_14;                         // 0x14
    u32 maxEntries;                     // 0x18: 0x7fffffff
    u32 unk_1c;                         // 0x1c
    u32 unk_20[4];                      // 0x20
} FsArchiveResource;

// Header block of an SRL image: the first 0x378 bytes (data_02129440). Byte 0x1c bit 0 is checked before loading.
typedef struct FsSrlHeader {
    u8 unk_00[0x1c];                    // 0x00
    u8 flags;                           // 0x1c
    u8 unk_1d[0x23];                    // 0x1d
    u32 fntOffset;                      // 0x40
    u32 fntSize;                        // 0x44
    u32 fatOffset;                      // 0x48
    u32 fatSize;                        // 0x4c
    u8 unk_50[0x328];                   // 0x50
} FsSrlHeader; // 0x378 bytes

extern FsSrlHeader data_02129440;

// Memory the SRL loader borrowed from the arena. Both lie outside the ARM9 image (linker symbols needed).
extern u32 data_021bfb04;               // start of the memory
extern u32 data_021bfb08;               // its size

// Result block of the ROM FAT FindPath command.
typedef struct FsPathResolved {
    u32 unk_00;                         // 0x00
    union {
        u32 word;
        struct {
            u16 lo;
            u16 hi;
        } half;
    } id;                               // 0x04
    u32 unk_08;                         // 0x08
} FsPathResolved;

// Result of the ROM FAT ReadDirectory command (FSDirEntry).
typedef struct FsDirEntry {
    u32 unk_00;                         // 0x00
    union {
        u32 word;
        struct {
            u16 lo;
            u16 hi;
        } half;
    } id;                               // 0x04
    u32 unk_08;                         // 0x08
    u32 isDirectory;                    // 0x0c
    u32 nameLength;                     // 0x10
    char name[0x80];                    // 0x14
} FsDirEntry; // 0x94 bytes

extern char data_020dfb70[]; // "rom": the ROM archive name
extern char data_020dfb74[]; // "rom:": its root directory
extern const FSArchiveVtbl data_020c90fc; // interface table of the ROM FAT archive (FSArchive.vtbl)

extern "C" {
s32 FsRom_Command(FSFile *file, s32 cmd);
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
s32 FSi_ROMFAT_OpenFileFast(FSArchive *arc, FSFile *file, u32 id, u32 mode); // mode is not used
s32 FSi_ROMFAT_SeekDirectory(FSArchive *arc, FSFile *file, u32 id, u32 position);
s32 FSi_ROMFAT_OpenFileDirect(FSArchive *arc, FSFile *file, u32 top, u32 bottom, const u32 *id);
s32 FSi_ROMFAT_OpenFile(FSArchive *arc, FSFile *file, u32 baseId, const char *path, u32 mode);
s32 FSi_ROMFAT_SeekFile(FSArchive *arc, FSFile *file, s32 *offset, s32 origin);
s32 FSi_ROMFAT_OpenDirectory(FSArchive *arc, FSFile *file, u32 baseId, const char *path);
// Outside the ARM9 image (linker symbols needed): helpers of the SRL loader func_02012264 and FSi_ReadSRLCallback.
u32 func_0218ac04(FsSrlHeader *header);  // the memory the image needs
void func_0218b0e4(u32 base, FsSrlHeader *header, u32 memory, u32 memorySize, void *readCallback, u32 flags, FSFile *file);
// 0x0218b768: reads from the archive base.
void func_0218b768(u32 base, void *dst, u32 src, u32 length);
s32 FSi_ROMFAT_GetPathInfo(FSArchive *arc, u32 baseId, const char *path, FsPathInfo *info);
s32 FSi_ROMFAT_GetArchiveResource(FSArchive *arc, FsArchiveResource *resource);
s32 FSi_ReadSRLCallback(FSArchive *arc, void *dst, u32 src, u32 length);
s32 FSi_ROMFAT_ReadDirectory(FSArchive *arc, FSFile *file, FsDirectoryEntryInfo *info);
s32 FSi_ROMFAT_FindPath(FSArchive *arc, u32 baseId, const char *path, u32 *resultId, s32 wantDirectory);
s32 FSi_ReadTable(FsTableReader *reader, void *dst, u32 length);

s32 FSi_IsUnreadableRomOffset(FSArchive *arc, u32 offset); // compares the archive name; offset (r1) is not used
void FSi_InitRomArchive(u32 dmaNo);
u32 func_02012264(FSArchive *arc, FSFile *srlFile, u32 base); // mounts an SRL image read through srlFile at base
}

#endif
