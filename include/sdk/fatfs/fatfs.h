#ifndef SDK_FATFS_FATFS_H
#define SDK_FATFS_FATFS_H

// TwlSDK FATFS library: FAT file system commands sent to the ARM7 driver through PXI. Each command fills a request
// buffer (FatfsRequest) and waits for the reply.
#include "types.h"
#include "sdk/os/os_thread.h"
#include "sdk/os/os_mutex.h"

#define FATFS_PATH_CHARS 0x116

typedef struct FatfsFileInfo {
    u32 words[0x8c];                    // 0x230 bytes of file/directory entry information
} FatfsFileInfo;

typedef struct FatfsDriveResource {
    u32 words[13];                      // 0x34 bytes
} FatfsDriveResource;

typedef struct FatfsRequest {
    u32 command;                        // 0x00
    s32 result;                         // 0x04: 0 on success
    u32 flags;                          // 0x08: bit 1 set while the command is asynchronous
    struct FatfsRequest *next;          // 0x0c
    union {                             // 0x10
        struct {
            u32 handle;                 // 0x10
            u32 value;                  // 0x14
            u32 length;                 // 0x18
        } io;
        struct {
            u32 handle;                 // 0x10
            char mode[0x10];            // 0x14
            u16 path[FATFS_PATH_CHARS]; // 0x24
        } open;
        struct {
            char mode[0x10];            // 0x10
            u16 path[FATFS_PATH_CHARS]; // 0x20
        } makeDirectory;
        struct {
            u16 path[FATFS_PATH_CHARS]; // 0x10
            u32 unk_23c;                // 0x23c
            FatfsFileInfo info;         // 0x240
        } info;
        struct {
            u16 from[FATFS_PATH_CHARS]; // 0x10
            u16 to[FATFS_PATH_CHARS];   // 0x23c
        } rename;
        struct {
            char name[0x10];            // 0x10
            FatfsDriveResource resource; // 0x20
        } drive;
        struct {
            u32 handle;                 // 0x10
            FatfsFileInfo entry;        // 0x14
        } directory;
        struct {
            char name[0x11c];           // 0x10
            u8 seed[8];                 // 0x12c
        } format;
        u8 raw[0x7f0];
    } arg;
    u32 threadHandle;                   // 0x800: thread that registered the buffer
    void (*callback)(struct FatfsRequest *request); // 0x804: completion callback
    u32 callbackArgument;               // 0x808
    struct FatfsRequest *nextRegistered; // 0x80c
} FatfsRequest;

#define FATFS_THREAD_HANDLE_IRQ 0x80000000

// One waiting thread: linked from FatfsState.waiters.
typedef struct FatfsWaiter {
    struct FatfsWaiter *next;           // 0x00
    u32 thread;                         // 0x04: thread handle
    FatfsRequest *request;              // 0x08: request buffer it uses
    s32 result;                         // 0x0c
} FatfsWaiter;

// data_021277e0 (0x6c bytes). The dsd symbols data_021277e4, data_02127800, data_02127820, data_02127828 and
// data_0212782c sit inside it.
typedef struct FatfsState {
    s32 lastResult;                     // 0x00
    FatfsWaiter *waiters;               // 0x04 (data_021277e4)
    u8 unk_08[0x18];
    FatfsRequest *registered;           // 0x20 (data_02127800): request buffers registered by threads
    u8 unk_24[0x1c];
    OsThreadQueue wakeQueue;            // 0x40 (data_02127820)
    FatfsRequest *pending;              // 0x48 (data_02127828): finished requests
    OsMutex mutex;                      // 0x4c (data_0212782c)
    FatfsRequest *commandBuffer;        // 0x64
    FatfsRequest *emergencyBuffer;      // 0x68
} FatfsState;

extern FatfsState data_021277e0;
extern FatfsRequest *data_020dfb3c;      // command buffer memory: two request buffers back to back

extern "C" {
FatfsRequest *FATFSi_AllocateCommandBuffer(u32 command);
FatfsRequest *FATFSi_AllocateEmergencyCommandBuffer(u32 command);
void FATFSi_FreeCommandBuffer(FatfsRequest *request);
void FATFSi_WaitForRequest(FatfsRequest *request);
void FATFSi_CopyString(char *dst, const char *src, s32 size);
void FATFSi_CopyUnicodeString(u16 *dst, const u16 *src, s32 size);
void FATFSi_ConvertArcnameToSjis(char *dst, const u16 *src);
void FATFSi_SyncInitialization(u32 arg);
s32 FATFS_FlushAll(void);
s32 FATFS_UnmountAll(void);
s32 FATFS_CloseFile(u32 handle);
s32 FATFS_ReadFile(u32 handle, u32 buffer, s32 length);
s32 FATFS_WriteFile(u32 handle, u32 buffer, s32 length);
s32 FATFS_SetSeekCache(u32 handle, u32 buffer, u32 length);
s32 FATFS_SeekFile(u32 handle, u32 offset, u32 origin);
s32 FATFS_FlushFile(u32 handle);
s32 FATFS_GetFileLength(u32 handle);
s32 FATFS_SetFileLength(u32 handle, u32 length);
s32 FATFS_CloseDirectory(u32 handle);
s32 FATFS_FormatSpecial(const char *name);
s32 FATFS_GetDriveResourceW(const u16 *name, FatfsDriveResource *resource);
s32 FATFS_GetFileInfoW(const u16 *path, FatfsFileInfo *info);
s32 FATFS_SetFileInfoW(const u16 *path, const FatfsFileInfo *info);
s32 FATFS_CreateFileW(const u16 *path, u32 mode, const char *attributes);
s32 FATFS_DeleteFileW(const u16 *path);
s32 FATFS_RenameFileW(const u16 *from, const u16 *to);
s32 FATFS_CreateDirectoryW(const u16 *path, const char *attributes);
s32 FATFS_DeleteDirectoryW(const u16 *path);
s32 FATFS_RenameDirectoryW(const u16 *from, const u16 *to);
u32 FATFS_OpenFileW(const u16 *path, const char *mode);
u32 FATFS_OpenDirectoryW(const u16 *path, const char *mode);
s32 FATFS_ReadDirectoryW(u32 handle, FatfsFileInfo *entry);
void FATFSi_InitRequest(void);
u32 FATFSi_GetThreadHandle(void);
void FATFSi_SetRequestBuffer(FatfsRequest *request, void (*callback)(FatfsRequest *), u32 argument);
void FATFSi_NotifyRequestCompletion(FatfsRequest *request);
void FATFSi_SendToPXI(FatfsRequest *request);
void FATFSi_PXICallback(u32 tag, u32 data, s32 err);
void Fatfs_SendToPxi(FatfsRequest *request); // tail call to FATFSi_SendToPXI (src/sdk/fatfs/fatfs_wrap.cpp)
}

#endif
