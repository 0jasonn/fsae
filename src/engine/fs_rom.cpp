#include "engine/functions.h"
#include "global.h"
#include "types.h"

// File handle with its archive pointer at +8.
typedef struct FsFile {
    u8 unk_00[8];
    void *archive;
} FsFile;

// ROM FAT archive: the archive kind at +0x24 is compared with data_020c90fc.
typedef struct FsArchive {
    u8 unk_00[0x24];
    u8 *kind;
} FsArchive;

extern u8 data_020c90fc[];

extern "C" s32 FSi_ROMFAT_GetFileLength(void *archive, FsFile *file, u32 arg);
extern "C" s32 FSi_ROMFAT_GetFilePosition(void *archive, FsFile *file, u32 arg);
extern "C" s32 FsRomFile_LengthIsZero(FsFile *file, u32 arg);
extern "C" s32 FsRomFile_PositionIsZero(FsFile *file, u32 arg);

// FsRomFile_LengthIsZero(file, arg) (0x02012488): 1 when the file is in the ROM FAT archive and its length is zero.
ARM s32 FsRomFile_LengthIsZero(FsFile *file, u32 arg) {
    FsArchive *archive;
    s32 result;

    archive = (FsArchive *)file->archive;
    result = 0;
    if (archive->kind == data_020c90fc) {
        result = (FSi_ROMFAT_GetFileLength(archive, file, arg) == 0);
    }
    return result;
}

// FsRomFile_PositionIsZero(file, arg) (0x020124c8): 1 when the file is in the ROM FAT archive and its position is zero.
ARM s32 FsRomFile_PositionIsZero(FsFile *file, u32 arg) {
    FsArchive *archive;
    s32 result;

    archive = (FsArchive *)file->archive;
    result = 0;
    if (archive->kind == data_020c90fc) {
        result = (FSi_ROMFAT_GetFilePosition(archive, file, arg) == 0);
    }
    return result;
}
