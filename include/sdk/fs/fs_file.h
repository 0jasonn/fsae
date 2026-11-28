#ifndef SDK_FS_FS_FILE_H
#define SDK_FS_FS_FILE_H

// TwlSDK FS file handle (FSFile) and the file functions. Only the fields the matched code touches are named; offsets
// are from the ROM.
#include "types.h"
#include "sdk/os/os_thread.h"

struct FSArchive;
struct FsDirectoryEntryInfo;

typedef struct FSFileProperty {
    u32 id;                             // 0x00 (file + 0x20)
    u32 top;                            // 0x04
    u32 bottom;                         // 0x08
    u32 pos;                            // 0x0c
} FSFileProperty;

// Argument words of a pending command, at file + 0x30. Which view applies depends on the command.
typedef struct FSFileCommand {
    union {
        void *buffer;
        const void *source;
        struct FSArchive *arc;
        u32 value;
    } a;                                // 0x30
    union {
        u32 word;
        struct {
            u16 lo;
            u16 hi;
        } half;
    } b;                                // 0x34
    union {
        u32 word;
        struct {
            u16 lo;
            u16 hi;
        } half;
    } c;                                // 0x38
    u32 unk_3c[3];
} FSFileCommand;

// FSFile.stat
#define FS_FILE_STAT_BUSY 0x01          // a command is queued or running
#define FS_FILE_STAT_CANCELED 0x02
#define FS_FILE_STAT_BLOCKING 0x04      // the caller waits (synchronous command)
#define FS_FILE_STAT_DONE 0x08          // asynchronous command finished, waiting thread not woken yet
#define FS_FILE_STAT_READY 0x40         // command selected to run
#define FS_FILE_STAT_COMMAND_SHIFT 8    // bits 8..15: running command

// Position inside a directory (the argument of the SeekDirectory command and the state of an open directory).
typedef struct FSDirPos {
    struct FSArchive *arc;              // 0x00
    union {
        u32 word;
        struct {
            u16 ownId;                  // 0x04: id of the directory being read
            u16 index;                  // 0x06: id handed out for the next file entry
        } half;
    } id;                               // 0x04
    u32 position;                       // 0x08: offset of the next entry in the file name table
} FSDirPos;

// View of FSFile +0x20 while the file is a directory being read.
typedef struct FSDirectoryProperty {
    FSDirPos pos;                       // 0x20
    u32 parent;                         // 0x2c
} FSDirectoryProperty;

// Entry of the directory table in the file name table (8 bytes per directory).
typedef struct FsDirectoryTableEntry {
    u32 offset;                         // 0x00: offset of the directory's first entry
    u16 firstId;                        // 0x04: id of its first file
    u16 parentId;                       // 0x06: parent directory (low 12 bits)
} FsDirectoryTableEntry;

typedef struct FSFile {
    struct FSFile *next;                // 0x00: next command queued on the archive
    FSFileProperty *prop;               // 0x04
    struct FSArchive *arc;              // 0x08
    u32 stat;                           // 0x0c
    void *argument;                     // 0x10: argument block of the running command
    s32 error;                          // 0x14
    OsThreadQueue queue;                // 0x18: threads waiting for the command
    union {
        FSFileProperty property;        // 0x20 (open file)
        FSDirectoryProperty dir;        // 0x20 (open directory)
    };
    union {
        FSFileCommand command;          // 0x30
        FSDirPos seek;                  // 0x30 (SeekDirectory command)
    };
} FSFile; // 0x48 bytes

// Argument blocks of the FS path commands (FSFile.argument).
// Create / get-path-info / create-directory commands: resolved path value, scratch buffer, extra word.
typedef struct FsPathArgsEx {
    u32 resolved;           // 0x00
    u8 *buffer;             // 0x04
    u32 extra;              // 0x08: mode or output pointer
} FsPathArgsEx;

// Change-directory (find path) command: resolved path value, scratch buffer, resulting directory id, flag.
typedef struct FsChangeDirectoryArgs {
    u32 resolved;           // 0x00
    u8 *buffer;             // 0x04
    u32 directory;          // 0x08: directory id found
    u32 flag;               // 0x0c: set to 1
} FsChangeDirectoryArgs;

// Delete commands.
typedef struct FsPathArgs {
    u32 resolved;           // 0x00
    u8 *buffer;             // 0x04
} FsPathArgs;

extern "C" {
void FS_InitFile(FSFile *file);
s32 FS_FindDir(FSFile *file, const char *path);
s32 FS_OpenFileDirect(FSFile *file, struct FSArchive *arc, u32 bottom, u32 id, u32 top);
s32 FS_CloseFile(FSFile *file);
s32 FS_CloseDirectory(FSFile *dir);
s32 FS_OpenDirectory(FSFile *dir, const char *path, u32 mode);
s32 FS_ReadDirectory(FSFile *dir, struct FsDirectoryEntryInfo *entry);
s32 FS_SetSeekCache(FSFile *file, void *buffer, u32 length);
s32 FS_SetFileLength(FSFile *file, u32 length);
s32 FSi_SeekDirDirect(FSFile *file, u16 entryId);
s32 FSi_SeekAndReadSRL(FSFile *file, void *buffer, s32 offset, s32 length);
s32 FSi_OpenFileDirectDefault(FSFile *file);

// Not decompiled yet.
u32 FS_GetFileLength(FSFile *file);
s32 FS_SeekFile(FSFile *file, s32 offset, s32 origin);
s32 FS_ReadFile(FSFile *file, void *buffer, s32 length);
s32 FS_ReadFileAsync(FSFile *file, void *buffer, s32 length);
s32 FS_WaitAsync(FSFile *file);
s32 FS_CreateFile(const char *path, u32 mode);
s32 FS_WriteFileAsync(FSFile *file, const void *buffer, u32 size);
s32 FSi_ReadFileDefault(FSFile *file);
s32 FSi_WriteFileDefault(FSFile *file);
s32 func_0200f69c(FSFile *file, u32 command, s32 blocking); // runs a command on the file
s32 FSi_TranslateCommand(FSFile *file, u32 command, s32 blocking);
s32 func_0200f068(FSFile *file, u32 command);
s32 FS_DeleteFile(const char *path);
s32 FS_GetPathInfo(const char *path, void *info);
s32 FS_CreateDirectory(const char *path, u32 mode);
s32 FS_DeleteDirectory(const char *path);
s32 FsRomFile_LengthIsZero(FSFile *file, u32 *length);
s32 FsRomFile_PositionIsZero(FSFile *file, u32 *position);
s32 FSi_SeekFileIfProc(FSFile *file, s32 offset, s32 origin); // ROM FAT archive: seeks directly, returns 1 when it did
}

#endif
