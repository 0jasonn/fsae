#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/sound/m4a.h"
#include "sdk/fs/fs_file.h"

// GzFile thunks, 0x0208e038 to 0x0208e05c: each one forwards to a TwlSDK file function (FS_CloseFile, FS_GetFileLength,
// FS_ReadFile). Provisional names are in scratch/agentD/renames.txt.

// GzFile_close (0x0208e038)
void GzFile_close(void *file) {
    FS_CloseFile((FSFile *)file);
}

// GzFile_getLength (0x0208e044)
u32 GzFile_getLength(void *file) {
    return FS_GetFileLength((FSFile *)file);
}

// GzFile_read (0x0208e050)
u32 GzFile_read(void *file, void *dst, u32 size) {
    return FS_ReadFile((FSFile *)file, dst, size);
}
