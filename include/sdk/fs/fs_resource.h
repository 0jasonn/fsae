#ifndef SDK_FS_FS_RESOURCE_H
#define SDK_FS_FS_RESOURCE_H

// TwlSDK FS archive resource (FSArchiveResource, 0x34 bytes): capacity of the archive's drive.
#include "types.h"

typedef struct FSArchiveResource {
    u64 totalSize;                      // 0x00
    u64 availableSize;                  // 0x08
    u32 maxFileSize;                    // 0x10
    u32 maxDirectoryDepth;              // 0x14
    u32 maxEntryNameLength;             // 0x18
    u32 maxPathNameLength;              // 0x1c
    u32 bytesPerSector;                 // 0x20
    u32 sectorsPerCluster;              // 0x24
    u32 totalClusters;                  // 0x28
    u32 availableClusters;              // 0x2c
} FSArchiveResource; // 0x30 bytes (TwlSDK; Knife_checkFileSpace keeps one on the stack)

extern "C" {
s32 FS_GetArchiveResource(const char *path, FSArchiveResource *resource);
u32 FSi_GetSpaceToCreateDirectoryEntries(const char *path, u32 clusterSize);
s32 FS_HasEnoughSpaceToCreateFile(FSArchiveResource *resource, const char *path, u32 size);
}

#endif
