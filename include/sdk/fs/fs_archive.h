#ifndef SDK_FS_FS_ARCHIVE_H
#define SDK_FS_FS_ARCHIVE_H

// TwlSDK FS archive (FSArchive, 0x5c bytes) and the archive functions. Only the fields the matched code touches are
// named; offsets are from the ROM.
#include "types.h"
#include "sdk/os/os_thread.h"

struct FSArchive;
struct FSFile;
typedef s32 (*FSArchiveAccessFunc)(struct FSArchive *arc, void *buffer, u32 offset, u32 length);

// Table the archive points at (FS_MountArchive's second argument): the memory base of the archive image, the file
// allocation table and file name table (offset and size, relative to the base) and the access callbacks.
typedef struct FSArchiveContext {
    u32 base;                           // 0x00
    union {
        u32 unk_04[7];                  // 0x04
        struct {
            u32 fat;                    // 0x04: offset of the file allocation table
            u32 fatSize;                // 0x08
            u32 fnt;                    // 0x0c: offset of the file name table
            u32 fntSize;                // 0x10
            u32 fatOriginal;            // 0x14: FAT offset kept while a loaded copy is in use
            u32 fntOriginal;            // 0x18
            void *loadedTables;         // 0x1c: memory FS_LoadArchiveTables copied the tables to; nonzero: the
                                        // tables are read with a plain memory copy (FSi_ReadTable)
        } t;
    };
    FSArchiveAccessFunc read;           // 0x20
    FSArchiveAccessFunc write;          // 0x24
    u32 unk_28;                         // 0x28
    s32 (*proc)(struct FSFile *file);   // 0x2c: event hook (FS_SetArchiveProc; FSi_TranslateCommand calls it)
    u32 procFlags;                      // 0x30: bit n set: the hook handles command n
} FSArchiveContext; // 0x34 bytes

// FSArchive.flag
#define FS_ARCHIVE_FLAG_NAMED 0x01      // registered in the archive list
#define FS_ARCHIVE_FLAG_MOUNTED 0x02
#define FS_ARCHIVE_FLAG_TABLES_LOADED 0x04
#define FS_ARCHIVE_FLAG_SUSPENDED 0x08
#define FS_ARCHIVE_FLAG_RUNNING 0x10    // a command is being executed
#define FS_ARCHIVE_FLAG_YIELD 0x20
#define FS_ARCHIVE_FLAG_SUSPENDING 0x40 // a suspend request is waiting for the running command
#define FS_ARCHIVE_FLAG_UNMOUNTING 0x80

// Archive interface: one handler per command number (see func_0200f068 for the argument shapes).
typedef struct FSArchiveVtbl {
    void *command[0x23];
} FSArchiveVtbl;

typedef struct FSArchive {
    union {
        s8 ptr[4];
        const char *longName;
    } name;                             // 0x00
    struct FSArchive *next;             // 0x04: next registered archive
    struct FSFile *list;                // 0x08: queued commands
    OsThreadQueue queue;                // 0x0c
    u32 flag;                           // 0x14: FS_ARCHIVE_FLAG_*
    u32 lastCommand;                    // 0x18
    s32 lastResult;                     // 0x1c: result of the last ROM FAT seek (FSi_SeekFileIfProc)
    FSArchiveContext *context;          // 0x20
    const FSArchiveVtbl *vtbl;          // 0x24: archive interface (data_020c90fc for the ROM FAT archive)
    FSArchiveContext ownContext;        // 0x28: the context FS_LoadArchive sets up (context points here)
} FSArchive; // 0x5c bytes

extern FSArchive data_021297c0;         // the ROM archive

extern "C" {
u32 FS_GetArchiveBase(FSArchive *arc);
u32 FS_GetArchiveOffset(FSArchive *arc, u32 offset);
const char *FS_GetArchiveName(FSArchive *arc);
s32 FS_IsArchiveTableLoaded(FSArchive *arc);
void FS_InitArchive(FSArchive *arc);
s32 FS_MountArchive(FSArchive *arc, FSArchiveContext *context, const FSArchiveVtbl *vtbl);
s32 FS_LoadArchive(FSArchive *arc, u32 base, u32 fat, u32 fatSize, u32 fnt, u32 fntSize, FSArchiveAccessFunc read,
                   FSArchiveAccessFunc write);
s32 func_0200fd08(FSArchive *arc, const char *name, u32 length); // FS_RegisterArchiveName (not matched yet)
void FS_SetArchiveProc(FSArchive *arc, void *proc, u32 flags);
s32 FSi_ReadMemCallback(FSArchive *arc, void *dst, u32 offset, u32 length);
s32 FSi_WriteMemCallback(FSArchive *arc, const void *src, u32 offset, u32 length);

u32 FS_LoadArchiveTables(FSArchive *arc, void *mem, u32 size);
void *FS_UnloadArchiveTables(FSArchive *arc);
s32 FS_SuspendArchive(FSArchive *arc);
s32 FS_ResumeArchive(FSArchive *arc);

void FS_NotifyArchiveAsyncEnd(FSArchive *arc, s32 result);
}

#endif
