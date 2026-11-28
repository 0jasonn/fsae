#include "global.h"
#include "types.h"
#include "sdk/mi/mi_memory.h"
#include "sdk/fs/fs_rom.h"

s32 FSi_ROMFAT_SeekDirectory(FSArchive *arc, FSFile *file, u32 id, u32 position) {
    s32 result;

    file->command.b.half.lo = id;
    file->arc = arc;
    file->command.a.arc = arc;
    file->command.b.half.hi = id >> 16;
    file->command.c.word = position;
    result = FSi_TranslateCommand(file, 2, 1);
    if (result == 0) {
        file->stat = (file->stat | 0x20) & ~0x10;
        file->prop = &file->property;
        file->arc = arc;
    }
    return result;
}

s32 FSi_ROMFAT_ReadDirectory(FSArchive *arc, FSFile *file, FsDirectoryEntryInfo *info) {
    u32 entryWords[2];
    FsTableReader reader;
    FsDirEntry entry;
    s32 result;
    u32 zero = 0;
    u32 nameLength;
    u32 id;

    file->command.a.value = (u32)&entry;
    file->command.b.word = zero;
    result = FSi_TranslateCommand(file, 3, 1);
    if (result == 0) {
        info->shortNameLength = zero;
        nameLength = entry.nameLength;
        info->longNameLength = nameLength;
        MI_CpuCopy8(entry.name, info->longName, nameLength);
        info->longName[info->longNameLength] = 0;
        if (entry.isDirectory != 0) {
            info->attributes = 0x100;
            info->id = entry.id.half.lo | (entry.id.half.hi << 16);
            info->fileSize = zero;
        } else {
            info->attributes = zero;
            id = entry.id.word;
            info->id = id;
            info->fileSize = zero;
            if (id * 8 < arc->context->t.fatSize) {
                reader.arc = arc;
                reader.offset = id * 8 + arc->context->t.fat;
                if (FSi_ReadTable(&reader, entryWords, 8) == 0) {
                    info->fileSize = entryWords[1] - entryWords[0];
                    if (FSi_IsUnreadableRomOffset(arc, entryWords[0])) {
                        info->attributes |= 0x400;
                    }
                }
            }
        }
        info->unk_138[0] = zero;
        info->unk_138[1] = zero;
        info->unk_138[2] = zero;
        info->unk_138[3] = zero;
        info->unk_138[4] = zero;
        info->unk_138[5] = zero;
    }
    return result;
}
