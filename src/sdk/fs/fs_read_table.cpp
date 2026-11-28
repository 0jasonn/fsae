#include "global.h"
#include "types.h"
#include "sdk/fs/fs_archive.h"
#include "sdk/fs/fs_file.h"
#include "sdk/fs/fs_command.h"
#include "sdk/fs/fs_rom.h"
#include "sdk/mi/mi_memory.h"

s32 FSi_ReadTable(FsTableReader *reader, void *dst, u32 length) {
    FSArchive *arc;
    FSArchiveContext *context;
    s32 result;

    arc = reader->arc;
    context = arc->context;
    if (context->t.loadedTables != 0) {
        MI_CpuCopy8((void *)reader->offset, dst, length);
        result = 0;
    } else {
        result = FSi_WaitForArchiveCompletion(arc->list, context->read(arc, dst, reader->offset, length));
    }
    reader->offset += length;
    return result;
}
