#ifndef WIP_G_G_CALLS_H
#define WIP_G_G_CALLS_H

// Calls made by the G units that are not in engine/functions.h yet (TwlSDK or dsd names, C linkage). The reviewer
// moves them to engine/functions.h.

#include "types.h"

extern "C" {
void TP_WaitBusy(s32 mode);
s32 TP_CheckError(s32 mode);
void SndSys_StopAll(void);
s32 Fs_ReleaseArchive(void *archive);
void func_0218a860(s32 arg);
void func_02012c40(void);
void OS_Terminate(void);
s32 ResCursor_InitRange(u8 *cursor);
}

#endif
