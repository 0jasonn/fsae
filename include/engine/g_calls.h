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
s32 func_0218a5d4(void);
s32 func_0218a5fc(void);
void func_02012c40(void);
void OS_Terminate(void);
}

#endif
