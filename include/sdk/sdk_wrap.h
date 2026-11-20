#ifndef WIP_A_SDK_WRAP_H
#define WIP_A_SDK_WRAP_H

#include "types.h"

// Prototypes for the TwlSDK and engine functions that the small wrappers in src/wip/A tail-call. The arguments are
// passed through unchanged, so the parameter lists only need the right number of registers.
extern "C" {
u32 STDi_GetUnicodeConversionTable(u32 a, u32 b, u32 c, u32 d);
u32 FATFSi_SendToPXI(u32 a, u32 b, u32 c, u32 d);
u32 FS_GetFileLength(u32 a, u32 b, u32 c, u32 d);
u32 FS_UnmountArchive(u32 a, u32 b, u32 c, u32 d);
u32 OSi_InitCommon(u32 a, u32 b, u32 c, u32 d);
u32 OSi_IrqCallback(u32 a, u32 b, u32 c, u32 d);
u32 OSi_DoLockByWord(u32 a, u32 b, u32 c, u32 d);
u32 OSi_DoUnlockByWord(u32 a, u32 b, u32 c, u32 d);
u32 OS_WaitEventEx(u32 a, u32 b, u32 c, u32 d);
u32 func_0201a070(u32 a, u32 b, u32 c, u32 d);
}

#endif
