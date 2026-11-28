#include "global.h"
#include "types.h"
#include "sdk/fs/fs_rom.h"

s32 FSi_ReadSRLCallback(FSArchive *arc, void *dst, u32 src, u32 length) {
    func_0218b768(FS_GetArchiveBase(arc), dst, src, length);
    return 0;
}
