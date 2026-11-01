#ifndef WIP_A_A_EXTERN_H
#define WIP_A_A_EXTERN_H

#include "types.h"

// Prototypes and data used by the files in src/wip/A that are not in engine/functions.h yet. The reviewer moves
// these into functions.h (see the report).
extern "C" {
u32 OS_DisableInterrupts(void);
void OS_RestoreInterrupts(u32 state);
void OS_Terminate(void);
void GX_VRAMCNT_SetLCDC_(u32 mask);
void DC_InvalidateRange(void *start, u32 size);
void FATFSi_InitRequest(void);
void FATFSi_SyncInitialization(u32 arg);
void RecordCursor_Fetch(void *context);
}

extern u16 data_02129864;
extern u32 data_020dfb40;
extern u32 data_02128920;

#endif
