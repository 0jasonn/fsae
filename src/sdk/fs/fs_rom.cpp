#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/fs/fs_rom.h"

extern u8 data_020c90fc[]; // interface table of the ROM FAT archive (FSArchive.vtbl)

extern "C" s32 FsRomFile_LengthIsZero(FSFile *file, u32 *length);
extern "C" s32 FsRomFile_PositionIsZero(FSFile *file, u32 *position);

// FsRomFile_LengthIsZero(file, length) (0x02012488): 1 when the file is in the ROM FAT archive and
// FSi_ROMFAT_GetFileLength succeeds (result 0; the length is stored in *length). The name is misleading.
s32 FsRomFile_LengthIsZero(FSFile *file, u32 *length) {
    FSArchive *archive;
    s32 result;

    archive = file->arc;
    result = 0;
    if (archive->vtbl == data_020c90fc) {
        result = (FSi_ROMFAT_GetFileLength(archive, file, length) == 0);
    }
    return result;
}

// FsRomFile_PositionIsZero(file, position) (0x020124c8): 1 when the file is in the ROM FAT archive and
// FSi_ROMFAT_GetFilePosition succeeds (result 0; the position is stored in *position). The name is misleading.
s32 FsRomFile_PositionIsZero(FSFile *file, u32 *position) {
    FSArchive *archive;
    s32 result;

    archive = file->arc;
    result = 0;
    if (archive->vtbl == data_020c90fc) {
        result = (FSi_ROMFAT_GetFilePosition(archive, file, position) == 0);
    }
    return result;
}
