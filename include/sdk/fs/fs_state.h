#ifndef SDK_FS_FS_STATE_H
#define SDK_FS_FS_STATE_H

// TwlSDK FS global state (data_02128924): the registered archive list, the current directory and the name buffers of
// archives with names longer than three characters.
#include "types.h"

struct FSArchive;

#define FS_ARCHIVE_NAME_BUFFERS 16
#define FS_ARCHIVE_NAME_LENGTH 16
#define FS_PATH_LENGTH 0x104

typedef struct FsState {
    struct FSArchive *archiveList;      // 0x00: first registered archive
    struct FSArchive *currentArchive;   // 0x04: archive of the current directory
    u16 currentDirectory;               // 0x08: directory id in that archive
    u16 unk_0a;                         // 0x0a
    u32 unk_0c;                         // 0x0c
    char archiveNames[FS_ARCHIVE_NAME_BUFFERS][FS_ARCHIVE_NAME_LENGTH]; // 0x10 (data_02128934)
} FsState; // 0x110 bytes

extern FsState data_02128924;
extern char data_02128a34[FS_PATH_LENGTH]; // current directory path

#endif
