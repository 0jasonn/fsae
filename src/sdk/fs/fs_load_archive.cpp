#include "global.h"
#include "types.h"
#include "sdk/fs/fs_rom.h"
#include "sdk/fs/fs_rom.h"
#include "sdk/fs/fs_archive.h"
#include "sdk/card/card.h"

s32 FS_LoadArchive(FSArchive *arc, u32 base, u32 fat, u32 fatSize, u32 fnt, u32 fntSize, FSArchiveAccessFunc read,
                   FSArchiveAccessFunc write) {
    arc->ownContext.base = base;
    arc->ownContext.t.fatSize = fatSize;
    arc->ownContext.t.fntSize = fntSize;
    arc->ownContext.t.fnt = fnt;
    arc->ownContext.t.fntOriginal = fnt;
    arc->ownContext.t.fat = fat;
    arc->ownContext.read = read ? read : FSi_ReadMemCallback;
    arc->ownContext.write = write ? write : (FSArchiveAccessFunc)FSi_WriteMemCallback;
    arc->ownContext.t.loadedTables = NULL;
    arc->ownContext.t.fatOriginal = fat;
    return FS_MountArchive(arc, &arc->ownContext, &data_020c90fc);
}
