#include "global.h"
#include "types.h"
#include "sdk/fs/fs_file.h"
#include "sdk/fs/fs_open.h"
#include "sdk/fs/fs_resource.h"
#include "sdk/std/std_string.h"
#include "sdk/fs/fs_api.h"

s32 FS_GetArchiveResource(const char *path, FSArchiveResource *resource) {
    FSFile file;
    FSArchive *arc;
    s32 result;
    FSArchiveResource *argument;

    result = 0;
    arc = func_0200f9fc(path, NULL, NULL);
    if (arc != NULL) {
        FS_InitFile(&file);
        file.arc = arc;
        file.argument = &argument;
        argument = resource;
        result = func_0200f69c(&file, 0x1c, 1);
    }
    return result;
}
