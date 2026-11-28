#include "global.h"
#include "types.h"
#include "engine/functions.h"
#include "sdk/fs/fs_archive.h"

void FS_InitArchive(FSArchive *arc) {
    MI_CpuFill8(arc, 0, 0x5c);
    arc->queue.tail = 0;
    arc->queue.head = 0;
}
