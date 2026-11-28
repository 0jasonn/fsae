#include "global.h"
#include "types.h"
#include "sdk/fs/fs_file.h"
#include "sdk/fs/fs_open.h"
#include "sdk/fs/fs_resource.h"
#include "sdk/std/std_string.h"
#include "sdk/fs/fs_api.h"

s32 FS_HasEnoughSpaceToCreateFile(FSArchiveResource *resource, const char *path, u32 size) {
    s32 result;
    u32 clusterSize;
    u32 needed;
    u32 clusters;

    clusterSize = resource->bytesPerSector * resource->sectorsPerCluster;
    result = 0;
    if (clusterSize != 0) {
        needed = ((size + (clusterSize - 1)) & ~(clusterSize - 1)) + FSi_GetSpaceToCreateDirectoryEntries(path, clusterSize);
        clusters = needed / clusterSize;
        if (clusters <= resource->availableClusters) {
            resource->availableClusters -= clusters;
            resource->availableSize -= needed;
            result = 1;
        }
    }
    return result;
}
