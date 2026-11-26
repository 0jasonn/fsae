#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/fs_dirfile_api.h"
#include "sdk/fs/obj_get24_api.h"
#include "sdk/fs/fs_file.h"

extern "C" u32 Fs_UnmountArchiveWrap(u32 archive);

// Fs_ReleaseArchive (Fs_ReleaseArchive, provisional name): unmounts the archive. When the unmount succeeds it runs
// func_0200fe08 on the archive and returns 1, otherwise 0.
s32 Fs_ReleaseArchive(void *archive) {
    if (Fs_UnmountArchiveWrap((u32)archive) == 0) {
        return 0;
    }
    func_0200fe08(archive);
    return 1;
}

// Fs_GetDirFileOffset (Fs_GetDirFileOffset, provisional name): looks up the directory path. When it is found, returns the base
// offset of the directory (word at +0x64 of the directory) plus the field at +0x24 of the file handle; returns 0 otherwise.
extern "C" s32 Fs_GetDirFileOffset(void *path);
s32 Fs_GetDirFileOffset(void *path) {
    FSFile file;
    u8 *dir;
    s32 offset;
    s32 fieldOffset;

    offset = 0;
    FS_InitFile(&file);
    if (FS_FindDir(&file, (const char *)path)) {
        dir = (u8 *)file.arc;
        fieldOffset = Obj_GetField24(&file);
        offset = *(s32 *)(dir + 0x64) + fieldOffset;
        FS_CloseFile(&file);
    }
    return offset;
}
