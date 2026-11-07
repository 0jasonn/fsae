#include "engine/functions.h"
#include "engine/narc_mount_e.h"

// NarcArchive_Mount (0x020c29c8): registers a NARC file in memory as a file system archive under name. The three
// sections are found by their magic ('BTAF', 'BTNF', 'GMIF'); the archive tables are loaded from them.
s32 NarcArchive_Mount(NarcArchive *archive, const u8 *name, u8 *narc) {
    NarcSection *fat = NULL;
    NarcSection *fnt = NULL;
    NarcSection *image = NULL;
    s32 i;
    NarcSection *section;
    s32 count;
    s32 zero;

    if (Narc_IsValidHeader(narc) == 0) {
        return 0;
    }
    section = (NarcSection *)(narc + *(u16 *)(narc + 0xc));
    count = *(u16 *)(narc + 0xe);
    for (i = 0; i < count; i++) {
        switch (section->magic) {
        case 0x46415442:
            fat = section;
            break;
        case 0x46494d47:
            image = section;
            break;
        case 0x464e5442:
            fnt = section;
            break;
        }
        section = (NarcSection *)((u8 *)section + section->size);
    }
    FS_InitArchive(archive);
    image = (NarcSection *)((u8 *)image + 8);
    archive->narc = narc;
    archive->fat = (u8 *)fat;
    archive->image = (u8 *)image;
    if (func_0200fd08(archive, name, Str_Length(name)) == 0) {
        return 0;
    }
    zero = 0;
    if (FS_LoadArchive(archive, (u32)image, (u32)fat + 0xc - (u32)image, fat->size - 0xc, (u32)fnt + 8 - (u32)image, fnt->size - 8, (void *)zero, (void *)zero) != 0) {
        return 1;
    }
    func_0200fe08(archive);
    return zero;
}
