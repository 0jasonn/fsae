#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/fs/fs_wrap_api.h"

// Tail call to FS_GetFileLength.
u32 Fs_GetFileLengthWrap(FSFile *file) {
    return FS_GetFileLength(file);
}
