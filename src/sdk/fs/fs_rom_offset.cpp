#include "global.h"
#include "types.h"
#include "sdk/std/std_string.h"
#include "sdk/fs/fs_rom.h"

// The comparison result is not used: no offset is ever reported as unreadable.
s32 FSi_IsUnreadableRomOffset(FSArchive *arc, u32 offset) {
    STD_CompareString(FS_GetArchiveName(arc), data_020dfb70);
    return 0;
}
