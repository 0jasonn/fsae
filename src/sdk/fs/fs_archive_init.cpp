#include "global.h"
#include "types.h"
#include "engine/functions.h"
#include "sdk/fs/fs_archive.h"

void FS_InitArchive(FSArchive *arc) {
    MI_CpuFill8(arc, 0, 0x5c);
    arc->unk_10 = 0;
    arc->unk_0c = 0;
}
