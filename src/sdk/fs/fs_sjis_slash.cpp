#include "global.h"
#include "types.h"
#include "engine/functions.h"
#include "sdk/fs/fs_api.h"
#include "sdk/std/std_string.h"

s32 FSi_DecrementSjisPositionToSlash(const u8 *path, s32 pos) {
    do {
        pos = FSi_DecrementSjisPosition((const char *)path, pos);
        if (pos < 0) {
            break;
        }
    } while (path[pos] != '/' && path[pos] != 0x5c);
    return pos;
}

s32 FSi_TrimSjisTrailingSlash(char *path) {
    s32 length = STD_GetStringLength(path);
    s32 pos = FSi_DecrementSjisPosition(path, length);

    if (pos >= 0) {
        u8 c = path[pos];
        if (c == '/' || c == 0x5c) {
            path[pos] = 0;
            length = pos;
        }
    }
    return length;
}
