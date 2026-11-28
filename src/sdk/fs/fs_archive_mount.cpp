#include "global.h"
#include "types.h"
#include "sdk/fs/fs_archive.h"
#include "sdk/fs/fs_file.h"

const char *FS_GetArchiveName(FSArchive *arc) {
    if (arc->name.ptr[3] != 0) {
        return arc->name.longName;
    }
    return (const char *)arc;
}

s32 FS_MountArchive(FSArchive *arc, FSArchiveContext *context, const FSArchiveVtbl *vtbl) {
    FSFile file;

    arc->context = context;
    arc->vtbl = vtbl;
    FS_InitFile(&file);
    file.arc = arc;
    func_0200f068(&file, 0x11);
    arc->flag |= 2;
    return 1;
}
