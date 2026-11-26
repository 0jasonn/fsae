#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/fs/fs_archive.h"

extern "C" void Fs_ResetArchiveSlots(FSArchive *arc);

// Fs_ResetArchiveSlots(arc) (0x02011ffc): checks the archive table (the result is unused; r0 still holds arc at the
// call), then clears the first seven words of the archive's context.
void Fs_ResetArchiveSlots(FSArchive *arc) {
    FSArchiveContext *context;

    context = arc->context;
    FS_IsArchiveTableLoaded(arc);
    context->base = 0;
    context->unk_04[0] = 0;
    context->unk_04[1] = 0;
    context->unk_04[2] = 0;
    context->unk_04[3] = 0;
    context->unk_04[4] = 0;
    context->unk_04[5] = 0;
}
