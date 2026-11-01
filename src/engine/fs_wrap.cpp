#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/sdk_wrap.h"
#include "engine/fs_wrap_api.h"

// Tail call to FS_GetFileLength.
u32 Fs_GetFileLengthWrap(u32 a, u32 b, u32 c, u32 d) {
    return FS_GetFileLength(a, b, c, d);
}
