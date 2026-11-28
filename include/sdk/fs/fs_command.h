#ifndef SDK_FS_FS_COMMAND_H
#define SDK_FS_FS_COMMAND_H

// TwlSDK FS command queue: commands are queued on an archive (FSArchive.list) and executed one at a time.
#include "types.h"
#include "sdk/fs/fs_file.h"

struct FSArchive;

extern "C" {
s32 FSi_IsEventCommand(u32 command);
void FSi_EndCommand(FSFile *file, s32 result);
s32 FSi_WaitForArchiveCompletion(FSFile *file, s32 result);
FSFile *FSi_NextCommand(struct FSArchive *arc, s32 wait);
void FSi_ExecuteAsyncCommand(FSFile *file);
void FSi_ExecuteSyncCommand(FSFile *file);
s32 FS_UnmountArchive(struct FSArchive *arc);
}

#endif
