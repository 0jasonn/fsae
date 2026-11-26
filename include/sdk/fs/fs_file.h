#ifndef SDK_FS_FS_FILE_H
#define SDK_FS_FS_FILE_H

// TwlSDK FS file handle (FSFile) and the file functions. Only the fields the matched code touches are named; offsets
// are from the ROM.
#include "types.h"

struct FSArchive;

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

typedef struct FSFile {
    u32 unk_00;                         // 0x00
    FSFileProperty *prop;               // 0x04
    struct FSArchive *arc;              // 0x08
    u32 stat;                           // 0x0c
    void *argument;                     // 0x10: argument block of the running command
    s32 error;                          // 0x14
    u32 queue[2];                       // 0x18
    FSFileProperty property;            // 0x20
    FSFileCommand command;              // 0x30
} FSFile; // 0x48 bytes

extern "C" {
void FS_InitFile(FSFile *file);
s32 FS_FindDir(FSFile *file, const char *path);
s32 FS_OpenFileDirect(FSFile *file, struct FSArchive *arc, u32 bottom, u32 id, u32 top);
s32 FS_CloseFile(FSFile *file);
s32 FS_CloseDirectory(FSFile *dir);
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
void FS_CreateFile(const char *path, u32 mode);
void FS_WriteFileAsync(FSFile *file, const void *buffer, u32 size);
s32 FSi_ReadFileDefault(FSFile *file);
s32 FSi_WriteFileDefault(FSFile *file);
s32 func_0200f69c(FSFile *file, u32 command, s32 blocking); // runs a command on the file
s32 FSi_TranslateCommand(FSFile *file, u32 command, s32 blocking);
s32 func_0200f068(FSFile *file, u32 command);
}

#endif
