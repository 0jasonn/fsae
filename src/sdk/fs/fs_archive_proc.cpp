#include "global.h"
#include "types.h"
#include "sdk/fs/fs_archive.h"

void FS_SetArchiveProc(FSArchive *arc, void *proc, u32 flags) {
    if (flags == 0) {
        proc = NULL;
    } else if (proc == NULL) {
        flags = 0;
    }
    arc->proc = proc;
    arc->procFlags = flags;
}
