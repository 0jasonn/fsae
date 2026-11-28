#ifndef SDK_FS_FS_API_H
#define SDK_FS_FS_API_H

// TwlSDK FS library setup (FS_Init, the ROM archive tables) and the Shift-JIS / Unicode path helpers.
#include "types.h"
#include "sdk/os/os_message.h"

// data_0212981c: set once FS_Init has run, and once the FAT driver is up.
typedef struct FsInitState {
    u32 fsInitialised;                  // 0x00
    u32 fatInitialised;                 // 0x04
} FsInitState;

// data_0212941c (0x20 bytes): overlay loading state, set up by FSi_InitOverlay.
typedef struct FsOverlayState {
    u32 unk_00;                         // 0x00
    struct FSArchive *romArchive;       // 0x04: the "rom" archive
    s32 unk_08;                         // 0x08: -1 for boot type 2, else 0
    u32 unk_0c;                         // 0x0c
    s32 unk_10;                         // 0x10: -1 for boot type 2, else 0
    u32 unk_14;                         // 0x14
    const void *table;                  // 0x18: data_020c8f7c
    u32 tableSize;                      // 0x1c: 0x40
} FsOverlayState;

extern FsOverlayState data_0212941c;
extern const u8 data_020c8f7c[0x40];
extern FsInitState data_0212981c;
extern u32 data_02128b38;               // set once the Unicode buffer pool is initialised
extern void *data_02128b3c[4];          // message storage of the queue below
extern OsMessageQueue data_02128b4c;    // message queue of the Unicode conversion buffers
extern u16 data_02128b6c[4][0x116];     // the four Unicode conversion buffers

extern char data_020dfb48[]; // "."
extern char data_020dfb4c[]; // ".."

extern "C" {
void FS_Init(u32 dmaNo);
u32 WBT_SetPacketSize(void *mem, u32 size); // dsd name: loads the file tables of the ROM archive (FS_LoadTable)
s32 FSi_DecrementSjisPosition(const char *str, s32 pos);
s32 FSi_DecrementSjisPositionToSlash(const u8 *path, s32 pos);
s32 FSi_TrimSjisTrailingSlash(char *path);
u16 *FSi_GetUnicodeBuffer(const char *path);
void FSi_ReleaseUnicodeBuffer(void *buffer);

void FSi_InitOverlay(void);
s32 FSi_IncrementSjisPositionToSlash(const char *path, s32 pos);

s32 FSi_ComplementDirectory(const char *path, char *buffer);
s32 FS_CreateDirectoryAuto(const char *path, u32 mode);
s32 FS_DeleteDirectoryAuto(const char *path);

// Not decompiled yet.
s32 FSi_GetFullPath(char *buffer, const char *path);
void FS_InitFatDriver(void);
}

#endif
