#include "engine/functions.h"
#include "game/rankingsave.h"
#include "global.h"

// Save buffer access and NAND helpers. Address -> name (original names):
//   0x02056b40 NAND_CreateDirectory
//   0x02056d00 ReadSaveBufferDword
//   0x02056ddc ProgramSaveBufferDwordEx
// The save buffer is the u16 table at KnifeApp + 0x4b0, four halfwords per dword index.

ARM s32 NAND_CreateDirectory(const char *path) {
    if (FS_CreateDirectoryAuto(path, 3) != 0) {
        return 1;
    }
    return FS_GetArchiveResultCode(path) == 8;
}
