#include "global.h"
#include "types.h"
#include "sdk/mi/mi_memory.h"
#include "sdk/fs/fs_rom.h"

u32 FS_LoadArchiveTables(FSArchive *arc, void *mem, u32 size) {
    FSArchiveContext *context;
    FSFile file;
    u32 needed;
    u8 *fatDest;
    u8 *fntDest;

    if (mem != NULL && FS_IsArchiveTableLoaded(arc)) {
        FS_UnloadArchiveTables(arc);
    }
    context = arc->context;
    needed = (context->t.fatSize + context->t.fntSize + 0x3f) & ~0x1f;
    if (needed <= size) {
        fatDest = (u8 *)(((u32)mem + 0x1f) & ~0x1f);
        FS_InitFile(&file);
        if (FS_OpenFileDirect(&file, arc, context->t.fat, context->t.fat + context->t.fatSize, 0xffffffff)) {
            if (FS_ReadFile(&file, fatDest, context->t.fatSize) < 0) {
                MI_CpuFill8(fatDest, 0, context->t.fatSize);
            }
            FS_CloseFile(&file);
        }
        context->t.fat = (u32)fatDest;
        fntDest = fatDest + context->t.fatSize;
        if (FS_OpenFileDirect(&file, arc, context->t.fnt, context->t.fnt + context->t.fntSize, 0xffffffff)) {
            if (FS_ReadFile(&file, fntDest, context->t.fntSize) < 0) {
                MI_CpuFill8(fntDest, 0, context->t.fntSize);
            }
            FS_CloseFile(&file);
        }
        context->t.fnt = (u32)fntDest;
        context->t.loadedTables = mem;
        arc->flag |= 4;
    }
    return needed;
}

void *FS_UnloadArchiveTables(FSArchive *arc) {
    void *loaded = NULL;
    FSArchiveContext *context;
    s32 wasRunning;
    s32 mounted = (arc->flag & 2) != 0;

    if (mounted) {
        context = arc->context;
        wasRunning = FS_SuspendArchive(arc);
        if (FS_IsArchiveTableLoaded(arc)) {
            arc->flag &= ~4;
            loaded = context->t.loadedTables;
            context->t.fat = context->t.fatOriginal;
            context->t.fnt = context->t.fntOriginal;
            context->t.loadedTables = NULL;
        }
        if (wasRunning) {
            FS_ResumeArchive(arc);
        }
    }
    return loaded;
}
