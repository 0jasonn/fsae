#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/fs/fs_wrap_api.h"

// TODO(headers): this declaration of FS_GetFileLength differs from the shared one; see the header restructure report.
extern "C" u32 FS_GetFileLength(u32 a, u32 b, u32 c, u32 d);

// Tail call to FS_GetFileLength.
u32 Fs_GetFileLengthWrap(u32 a, u32 b, u32 c, u32 d) {
    return FS_GetFileLength(a, b, c, d);
}
