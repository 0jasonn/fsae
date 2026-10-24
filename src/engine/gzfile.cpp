#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/m4a.h"

// GzFile thunks, 0x0208e038 to 0x0208e05c: each one forwards to a TwlSDK file function (FS_CloseFile, FS_GetFileLength,
// FS_ReadFile). Provisional names are in scratch/agentD/renames.txt.
extern "C" void FS_CloseFile(void *file);
extern "C" u32 FS_GetFileLength(void *file);
extern "C" u32 FS_ReadFile(void *file, void *dst, u32 size);

// GzFile_close (0x0208e038)
extern "C" void GzFile_close(void *file);
ARM void GzFile_close(void *file) {
    FS_CloseFile(file);
}

// GzFile_getLength (0x0208e044)
extern "C" u32 GzFile_getLength(void *file);
ARM u32 GzFile_getLength(void *file) {
    return FS_GetFileLength(file);
}

// GzFile_read (0x0208e050)
extern "C" u32 GzFile_read(void *file, void *dst, u32 size);
ARM u32 GzFile_read(void *file, void *dst, u32 size) {
    return FS_ReadFile(file, dst, size);
}
