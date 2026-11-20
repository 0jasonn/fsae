#ifndef KNIFE_COMM_WM_IDLE2PARENT_H
#define KNIFE_COMM_WM_IDLE2PARENT_H

#include "types.h"

// Names passed to handleResult by update_idle2parent (rodata strings)
extern char data_0211b1e8[]; // "WM_MeasureChannel"
extern char data_0211b1fc[]; // "WM_SetParentParameter"
extern char data_0211b214[]; // "WM_StartParent"
extern char data_0211b224[]; // "WM_StartMP"

extern "C" {
s32 WM_MeasureChannel(void *callback, u16 unk1, u16 unk2, u16 channel, u16 unk4);
s32 WM_SetParentParameter(void *callback, void *parentParam);
void Knife_Comm_WirelessManager_update_idle2parent(void *self);
}

#endif
