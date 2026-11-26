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

extern FsInitState data_0212981c;
extern OsMessageQueue data_02128b4c;    // message queue of the Unicode conversion buffers

extern "C" {
void FS_Init(u32 dmaNo);
u32 WBT_SetPacketSize(void *mem, u32 size); // dsd name: loads the file tables of the ROM archive (FS_LoadTable)
s32 FSi_DecrementSjisPosition(const char *str, s32 pos);
s32 FSi_DecrementSjisPositionToSlash(const u8 *path, s32 pos);
s32 FSi_TrimSjisTrailingSlash(char *path);
void FSi_ReleaseUnicodeBuffer(void *buffer);

// Not decompiled yet.
void FSi_InitOverlay(void);
void FS_InitFatDriver(void);
}

#endif
