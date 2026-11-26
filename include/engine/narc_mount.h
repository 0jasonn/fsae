#ifndef ENGINE_NARC_MOUNT_H
#define ENGINE_NARC_MOUNT_H

#include "engine/functions.h"
#include "engine/narc_check_api.h"
#include "engine/str_api.h"
#include "sdk/fs/fs_archive.h"

// Section header of a NARC file: magic ('BTAF' file table, 'BTNF' name table, 'GMIF' image) and size
typedef struct NarcSection {
    u32 magic;
    u32 size;
} NarcSection;

// NARC archive: an FSArchive of the SDK followed by the NARC pointers
typedef struct NarcArchive {
    FSArchive arc;
    u8 *narc;      // 0x5c: the NARC file in memory
    u8 *fat;       // 0x60: file table section
    u8 *image;     // 0x64: start of the file image (after the GMIF section header)
} NarcArchive;

extern "C" {
s32 func_0200fd08(NarcArchive *archive, const u8 *name, u32 length); // FS_RegisterArchiveName
s32 FS_LoadArchive(NarcArchive *archive, u32 base, u32 fat, u32 fatSize, u32 fnt, u32 fntSize, void *readFunc, void *writeFunc);
s32 NarcArchive_Mount(NarcArchive *archive, const u8 *name, u8 *narc);
}

#endif
