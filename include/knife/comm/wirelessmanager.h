#ifndef WIP_D_WIRELESSMANAGER_H
#define WIP_D_WIRELESSMANAGER_H

#include "types.h"
#include "knife/comm/wm_d.h"
#include "knife/comm/wm_irq.h"

// Knife::Comm::WirelessManager prototypes of the wip units; functions.h is not included by the units that define functions
// whose return types differ there (turnOn, turnOff, reset return BOOL).
s32 func_02090ecc(void *manager);

// Knife::Comm::WirelessManager vtable pointer (rodata), stored at +0 of the manager by the constructor.
extern char data_0211b0c4[];
extern char data_0211b180[];  // the name passed to handleResult for WM_SetEntry (rodata)
extern char data_0211b130[];  // name for handleResult after WM_EndDataSharing (rodata)
extern char data_0211b144[];  // name for handleResult after WM_EndMP (rodata)
extern char data_0211b0dc[];
extern char data_0211b0e8[];
extern char data_0211b0f4[];
extern char data_0211b100[];
extern char data_0211b19c[];  // the name passed to handleResult by internalReset (rodata)
extern char data_0211b160[];  // the name passed to handleResult after WM_EndDataSharing in disconnect (rodata)
extern char data_0211b174[];  // the name passed to handleResult after WM_EndMP in disconnect (rodata)
extern char data_0211b18c[];  // the name passed to handleResult after WM_SetGameInfo (rodata)
extern char data_0211b230[];  // the name passed to handleResult by update_parent (rodata)
extern char data_0211b260[];  // the name passed to handleResult by update_child (rodata)
extern char data_0211b254[];  // the name passed to handleResult by update_idle2child (rodata)

// Frame helpers of the scope cleanup: the array constructor (C++ linkage, _Z14Frame_LoopC7b8PvlmS_S_) and the array
// destructor (plain name).
void Frame_LoopC7b8(void *array, s32 count, u32 size, void *ctor, void *dtor);

extern "C" {
void Frame_LoopC868(void *array, s32 count, u32 size, void *dtor);
void *Knife_Comm_WirelessManager_dtor_WirelessManager_0923fc(void *self);
void Knife_Comm_WirelessManager_stepNextChannel(void *self);
BOOL Knife_Comm_WirelessManager_setEntry(void *self, BOOL flag);
u32 WM_SetEntry(void *callback, BOOL flag);
s32 WM_StartMP(void *callback, void *recvBuf, u16 recvSize, void *sendBuf, u16 sendSize, s32 flag);
s32 WM_GetAID(void);
s32 WM_GetConnectedAIDs(void);
void Knife_Comm_WirelessManager_callback_WM_StartMP(void *result);
s32 WM_EndDataSharing(void *buf);
s32 WM_EndMP(void *callback);
s32 WM_SetGameInfo(void *callback, void *gameInfo, u16 unk2, u32 unk3, u16 unk4, u8 unk5);
s32 Knife_Comm_WirelessManager_getLinkLevel(void *self);
BOOL Knife_Comm_WirelessManager_updateUserGameInfo(void *self);
void Knife_Comm_WirelessManager_update_parent(void *self);
void Knife_Comm_WirelessManager_update_child(void *self);
s32 WM_StepDataSharing(void *buf, void *sendBuf, void *recvBuf);
void *WM_GetSharedDataAddress(void *buf, void *table, u16 index);
void MI_CpuFill8(void *dst, u32 value, u32 size);
s32 func_02019968(void);
s32 func_0201f838(void *callback);
s32 WM_PowerOff(void *callback);
s32 WM_Reset(void *callback);
void Knife_Comm_WirelessManager_callback_WM_EnableStep(void *result);
void Knife_Comm_WirelessManager_callback_WM_PowerOffStep(void *result);
void Knife_Comm_WirelessManager_callback_WM_Reset(void *result);
void Knife_Comm_WirelessManager_update_idle2child(void *self);
}

#endif
