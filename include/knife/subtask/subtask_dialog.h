#ifndef WIP_E_SUBTASK_DIALOG_H
#define WIP_E_SUBTASK_DIALOG_H

// subtask_dialogWaitSend (0x020abf5c): waits until the dialog object is idle, sends the block of the table entry and
// returns 1; plays the error sound and returns 0 when the send fails. Defined in src/wip/E/subtask_dialog.cpp.
// func_020909c8 and SoundReq are declared in engine/functions.h.

#include "engine/functions.h"

extern "C" {
BOOL subtask_dialogWaitSend(void);
void Knife_Comm_WirelessManager_update(void *obj);
s32 Knife_Comm_WirelessManager_startParent(void *obj, s32 kind, s32 size, void *data, s32 flag);
void OS_WaitVBlankIntr(void);
}

#endif
