#include "global.h"
#include "types.h"
#include "sdk/fs/fs_file.h"
#include "sdk/fs/fs_api.h"
#include "sdk/fs/fs_path.h"
#include "sdk/fs/fs_rom.h"
#include "sdk/std/std_string.h"

s32 FS_DeleteDirectoryAuto(const char *path) {
    char buffer[0x118];
    FSFile directory;
    FsDirectoryEntryInfo entry;
    s32 tryDelete;
    s32 baseLength;
    s32 failed;
    char *end;
    s32 position;
    s32 namePosition;

    position = 0;
    if (path != NULL && path[0] != 0 && FSi_GetFullPath(buffer, path) != 0) {
        baseLength = FSi_TrimSjisTrailingSlash(buffer);
        end = buffer + baseLength;
        tryDelete = 1;
        do {
            end[position] = 0;
            failed = 0;
            if (tryDelete != 0) {
                if (FS_DeleteDirectory(buffer) != 0 || FS_GetArchiveResultCode(buffer) == 8) {
                    position = FSi_DecrementSjisPositionToSlash((const u8 *)end, position);
                    continue;
                }
            }
            FS_InitFile(&directory);
            if (FS_OpenDirectory(&directory, buffer, 1) == 0) {
                failed = 1;
                continue;
            }
            tryDelete = 1;
            end[position] = '/';
            if (FS_ReadDirectory(&directory, &entry) != 0) {
                namePosition = baseLength + position + 1;
                do {
                    STD_CopyString(buffer + namePosition, entry.longName);
                    if ((entry.attributes & 0x100) == 0) {
                        if (FS_DeleteFile(buffer) == 0) {
                            failed = 1;
                            break;
                        }
                    } else if (STD_CompareString(entry.longName, data_020dfb48) != 0 && STD_CompareString(entry.longName, data_020dfb4c) != 0
                               && FS_DeleteDirectory(buffer) == 0) {
                        position += STD_GetStringLength(entry.longName) + 1;
                        tryDelete = 0;
                        break;
                    }
                } while (FS_ReadDirectory(&directory, &entry) != 0);
            }
            FS_CloseDirectory(&directory);
        } while (failed == 0 && position >= 0);
        position = position < 0 ? 1 : 0;
    }
    return position;
}
