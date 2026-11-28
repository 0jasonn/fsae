#include "global.h"
#include "types.h"
#include "sdk/fs/fs_file.h"
#include "sdk/fs/fs_api.h"
#include "sdk/fs/fs_rom.h"
#include "sdk/std/std_string.h"

s32 FSi_ComplementDirectory(const char *path, char *buffer) {
    FsPathInfo info;
    s32 result;
    s32 created;
    s32 end;
    s32 position;
    s32 found;

    result = 0;
    created = 0;
    if (FSi_GetFullPath(buffer, path) != 0 && STD_GetStringLength(buffer) > 0) {
        end = FSi_TrimSjisTrailingSlash(buffer);
        position = end = FSi_DecrementSjisPositionToSlash((const u8 *)buffer, end);
        if (position >= 0) {
            do {
                buffer[position] = 0;
                found = FS_GetPathInfo(buffer, &info);
                buffer[position] = '/';
                if (found == 0) {
                    position = FSi_DecrementSjisPositionToSlash((const u8 *)buffer, position);
                    continue;
                }
                if ((info.attributes & 0x100) == 0) {
                    position = -1;
                } else {
                    position++;
                }
                break;
            } while (position >= 0);
        }
        if (position >= 0) {
            while (1) {
                if (position >= end) {
                    result = 1;
                    break;
                }
                position = FSi_IncrementSjisPositionToSlash(buffer, position);
                buffer[position] = 0;
                if (FS_CreateDirectory(buffer, 3) == 0) {
                    break;
                }
                if (created == 0) {
                    created = position;
                }
                buffer[position] = '/';
                position++;
            }
        }
    }
    buffer[created] = 0;
    return result;
}
