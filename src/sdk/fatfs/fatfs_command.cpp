#include "global.h"
#include "types.h"
#include "sdk/fatfs/fatfs.h"
#include "engine/functions.h"
#include "sdk/pxi/pxi_fifo.h"
#include "sdk/card/card.h"
#include "sdk/os/dc_cache.h"
#include "sdk/os/os_interrupts.h"
#include "sdk/fatfs/stdconv_table_wrap_api.h"

s32 FATFS_FlushAll(void) {
    FatfsRequest *request;
    s32 success;

    request = FATFSi_AllocateEmergencyCommandBuffer(0x19);
    Fatfs_SendToPxi(request);
    FATFSi_WaitForRequest(request);
    success = (request->result == 0);
    FATFSi_FreeCommandBuffer(request);
    return success;
}

s32 FATFS_UnmountAll(void) {
    FatfsRequest *request;
    s32 success;

    request = FATFSi_AllocateEmergencyCommandBuffer(0x1a);
    Fatfs_SendToPxi(request);
    FATFSi_WaitForRequest(request);
    success = (request->result == 0);
    FATFSi_FreeCommandBuffer(request);
    return success;
}

s32 FATFS_CloseFile(u32 handle) {
    FatfsRequest *request;
    s32 success;

    request = FATFSi_AllocateCommandBuffer(0xf);
    request->arg.io.handle = handle;
    Fatfs_SendToPxi(request);
    FATFSi_WaitForRequest(request);
    success = (request->result == 0);
    FATFSi_FreeCommandBuffer(request);
    return success;
}

s32 FATFS_ReadFile(u32 handle, u32 buffer, s32 length) {
    FatfsRequest *request;

    request = FATFSi_AllocateCommandBuffer(0x10);
    request->arg.io.handle = handle;
    request->arg.io.value = buffer;
    request->arg.io.length = length;
    Fatfs_SendToPxi(request);
    if ((request->flags & 2) == 0) {
        FATFSi_WaitForRequest(request);
        length = request->arg.io.length;
        FATFSi_FreeCommandBuffer(request);
    }
    return length;
}

s32 FATFS_WriteFile(u32 handle, u32 buffer, s32 length) {
    FatfsRequest *request;

    request = FATFSi_AllocateCommandBuffer(0x11);
    request->arg.io.handle = handle;
    request->arg.io.value = buffer;
    request->arg.io.length = length;
    Fatfs_SendToPxi(request);
    if ((request->flags & 2) == 0) {
        FATFSi_WaitForRequest(request);
        length = request->arg.io.length;
        FATFSi_FreeCommandBuffer(request);
    }
    return length;
}

s32 FATFS_SetSeekCache(u32 handle, u32 buffer, u32 length) {
    FatfsRequest *request;
    s32 success;

    request = FATFSi_AllocateCommandBuffer(0x1d);
    request->arg.io.handle = handle;
    request->arg.io.value = buffer;
    request->arg.io.length = length;
    Fatfs_SendToPxi(request);
    FATFSi_WaitForRequest(request);
    success = (request->result == 0);
    FATFSi_FreeCommandBuffer(request);
    return success;
}

s32 FATFS_SeekFile(u32 handle, u32 offset, u32 origin) {
    FatfsRequest *request;
    s32 position;

    request = FATFSi_AllocateCommandBuffer(0x12);
    request->arg.io.handle = handle;
    request->arg.io.value = offset;
    request->arg.io.length = origin;
    Fatfs_SendToPxi(request);
    FATFSi_WaitForRequest(request);
    if (request->result == 0) {
        position = request->arg.io.value;
    } else {
        position = -1;
    }
    FATFSi_FreeCommandBuffer(request);
    return position;
}

s32 FATFS_FlushFile(u32 handle) {
    FatfsRequest *request;
    s32 success;

    request = FATFSi_AllocateCommandBuffer(0x13);
    request->arg.io.handle = handle;
    Fatfs_SendToPxi(request);
    FATFSi_WaitForRequest(request);
    success = (request->result == 0);
    FATFSi_FreeCommandBuffer(request);
    return success;
}

s32 FATFS_GetFileLength(u32 handle) {
    FatfsRequest *request;
    s32 length;

    request = FATFSi_AllocateCommandBuffer(0x14);
    request->arg.io.handle = handle;
    Fatfs_SendToPxi(request);
    FATFSi_WaitForRequest(request);
    if (request->result == 0) {
        length = request->arg.io.value;
    } else {
        length = -1;
    }
    FATFSi_FreeCommandBuffer(request);
    return length;
}

s32 FATFS_SetFileLength(u32 handle, u32 length) {
    FatfsRequest *request;
    s32 success;

    request = FATFSi_AllocateCommandBuffer(0x15);
    request->arg.io.handle = handle;
    request->arg.io.value = length;
    Fatfs_SendToPxi(request);
    FATFSi_WaitForRequest(request);
    success = (request->result == 0);
    FATFSi_FreeCommandBuffer(request);
    return success;
}

s32 FATFS_CloseDirectory(u32 handle) {
    FatfsRequest *request;
    s32 success;

    request = FATFSi_AllocateCommandBuffer(0x17);
    request->arg.io.handle = handle;
    Fatfs_SendToPxi(request);
    FATFSi_WaitForRequest(request);
    success = (request->result == 0);
    FATFSi_FreeCommandBuffer(request);
    return success;
}

s32 FATFS_FormatSpecial(const char *name) {
    u8 seed[0x20];
    FatfsRequest *request;
    s32 success;

    request = FATFSi_AllocateCommandBuffer(0x1e);
    OS_GetLowEntropyData(seed);
    func_0200dea0(seed, seed, sizeof(seed));
    FATFSi_CopyString(request->arg.format.name, name, FATFS_PATH_CHARS);
    MI_CpuCopy(seed, request->arg.format.seed, 8);
    Fatfs_SendToPxi(request);
    FATFSi_WaitForRequest(request);
    success = (request->result == 0);
    FATFSi_FreeCommandBuffer(request);
    return success;
}

s32 FATFS_GetDriveResourceW(const u16 *name, FatfsDriveResource *resource) {
    s32 success;
    FatfsRequest *request;

    success = 0;
    request = FATFSi_AllocateCommandBuffer(4);
    FATFSi_ConvertArcnameToSjis(request->arg.drive.name, name);
    Fatfs_SendToPxi(request);
    FATFSi_WaitForRequest(request);
    if (request->result == 0) {
        *resource = request->arg.drive.resource;
        success = 1;
    }
    FATFSi_FreeCommandBuffer(request);
    return success;
}

s32 FATFS_GetFileInfoW(const u16 *path, FatfsFileInfo *info) {
    s32 success;
    FatfsRequest *request;

    success = 0;
    request = FATFSi_AllocateCommandBuffer(6);
    FATFSi_CopyUnicodeString(request->arg.info.path, path, FATFS_PATH_CHARS);
    Fatfs_SendToPxi(request);
    FATFSi_WaitForRequest(request);
    if (request->result == 0) {
        *info = request->arg.info.info;
        success = 1;
    }
    FATFSi_FreeCommandBuffer(request);
    return success;
}

s32 FATFS_SetFileInfoW(const u16 *path, const FatfsFileInfo *info) {
    FatfsRequest *request;
    s32 success;

    request = FATFSi_AllocateCommandBuffer(7);
    FATFSi_CopyUnicodeString(request->arg.info.path, path, FATFS_PATH_CHARS);
    request->arg.info.info = *info;
    Fatfs_SendToPxi(request);
    FATFSi_WaitForRequest(request);
    success = (request->result == 0);
    FATFSi_FreeCommandBuffer(request);
    return success;
}

s32 FATFS_CreateFileW(const u16 *path, u32 mode, const char *attributes) {
    FatfsRequest *request;
    s32 success;

    request = FATFSi_AllocateCommandBuffer(8);
    request->arg.open.handle = mode;
    FATFSi_CopyString(request->arg.open.mode, attributes, 0x10);
    FATFSi_CopyUnicodeString(request->arg.open.path, path, FATFS_PATH_CHARS);
    Fatfs_SendToPxi(request);
    FATFSi_WaitForRequest(request);
    success = (request->result == 0);
    FATFSi_FreeCommandBuffer(request);
    return success;
}

s32 FATFS_DeleteFileW(const u16 *path) {
    FatfsRequest *request;
    s32 success;

    request = FATFSi_AllocateCommandBuffer(9);
    FATFSi_CopyUnicodeString(request->arg.info.path, path, FATFS_PATH_CHARS);
    Fatfs_SendToPxi(request);
    FATFSi_WaitForRequest(request);
    success = (request->result == 0);
    FATFSi_FreeCommandBuffer(request);
    return success;
}

s32 FATFS_RenameFileW(const u16 *from, const u16 *to) {
    FatfsRequest *request;
    s32 success;

    request = FATFSi_AllocateCommandBuffer(10);
    FATFSi_CopyUnicodeString(request->arg.rename.from, from, FATFS_PATH_CHARS);
    FATFSi_CopyUnicodeString(request->arg.rename.to, to, FATFS_PATH_CHARS);
    Fatfs_SendToPxi(request);
    FATFSi_WaitForRequest(request);
    success = (request->result == 0);
    FATFSi_FreeCommandBuffer(request);
    return success;
}

s32 FATFS_CreateDirectoryW(const u16 *path, const char *attributes) {
    FatfsRequest *request;
    s32 success;

    request = FATFSi_AllocateCommandBuffer(11);
    FATFSi_CopyString(request->arg.makeDirectory.mode, attributes, 0x10);
    FATFSi_CopyUnicodeString(request->arg.makeDirectory.path, path, FATFS_PATH_CHARS);
    Fatfs_SendToPxi(request);
    FATFSi_WaitForRequest(request);
    success = (request->result == 0);
    FATFSi_FreeCommandBuffer(request);
    return success;
}

s32 FATFS_DeleteDirectoryW(const u16 *path) {
    FatfsRequest *request;
    s32 success;

    request = FATFSi_AllocateCommandBuffer(12);
    FATFSi_CopyUnicodeString(request->arg.info.path, path, FATFS_PATH_CHARS);
    Fatfs_SendToPxi(request);
    FATFSi_WaitForRequest(request);
    success = (request->result == 0);
    FATFSi_FreeCommandBuffer(request);
    return success;
}

s32 FATFS_RenameDirectoryW(const u16 *from, const u16 *to) {
    FatfsRequest *request;
    s32 success;

    request = FATFSi_AllocateCommandBuffer(13);
    FATFSi_CopyUnicodeString(request->arg.rename.from, from, FATFS_PATH_CHARS);
    FATFSi_CopyUnicodeString(request->arg.rename.to, to, FATFS_PATH_CHARS);
    Fatfs_SendToPxi(request);
    FATFSi_WaitForRequest(request);
    success = (request->result == 0);
    FATFSi_FreeCommandBuffer(request);
    return success;
}

u32 FATFS_OpenFileW(const u16 *path, const char *mode) {
    FatfsRequest *request;
    u32 handle;

    request = FATFSi_AllocateCommandBuffer(14);
    request->arg.open.handle = 0;
    FATFSi_CopyString(request->arg.open.mode, mode, 0x10);
    FATFSi_CopyUnicodeString(request->arg.open.path, path, FATFS_PATH_CHARS);
    Fatfs_SendToPxi(request);
    FATFSi_WaitForRequest(request);
    handle = request->arg.open.handle;
    FATFSi_FreeCommandBuffer(request);
    return handle;
}

u32 FATFS_OpenDirectoryW(const u16 *path, const char *mode) {
    FatfsRequest *request;
    u32 handle;

    request = FATFSi_AllocateCommandBuffer(0x16);
    request->arg.open.handle = 0;
    FATFSi_CopyString(request->arg.open.mode, mode, 0x10);
    FATFSi_CopyUnicodeString(request->arg.open.path, path, FATFS_PATH_CHARS);
    Fatfs_SendToPxi(request);
    FATFSi_WaitForRequest(request);
    handle = request->arg.open.handle;
    FATFSi_FreeCommandBuffer(request);
    return handle;
}

s32 FATFS_ReadDirectoryW(u32 handle, FatfsFileInfo *entry) {
    s32 success;
    FatfsRequest *request;

    success = 0;
    request = FATFSi_AllocateCommandBuffer(0x18);
    request->arg.directory.handle = handle;
    Fatfs_SendToPxi(request);
    FATFSi_WaitForRequest(request);
    if (request->result == 0) {
        *entry = request->arg.directory.entry;
        success = 1;
    }
    FATFSi_FreeCommandBuffer(request);
    return success;
}
