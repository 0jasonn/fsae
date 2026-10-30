#ifndef WIP_A_FS_OPEN_H
#define WIP_A_FS_OPEN_H

// Declarations for src/wip/A/fs_open.cpp. Parameter types follow the call sites in the ROM.
#include "types.h"

// Argument block passed to the loader through FsOpenRecord.args.
typedef struct FsOpenArgs {
    u32 resolved;           // 0x00: value written by the path resolver
    u8 *buffer;             // 0x04: scratch buffer that was handed to the resolver
    u32 arg;                // 0x08: second argument of FsFile_OpenPath
} FsOpenArgs;

// Record that FsFile_OpenPath fills. Only the fields it writes are named.
typedef struct FsOpenRecord {
    u8 unk_00[8];
    s32 handle;             // 0x08: result of the path resolver, cleared when the load fails
    u8 unk_0c[4];
    FsOpenArgs *args;       // 0x10
} FsOpenRecord;

extern "C" {
s32 func_0200f9fc(u32 path, u32 *resolved, u8 *buffer);
s32 func_0200f69c(FsOpenRecord *rec, u32 mode, s32 flag);
void FS_InitFile(void *file);
}

#endif
