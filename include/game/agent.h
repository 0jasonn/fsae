#ifndef WIP_A_AGENT_A_H
#define WIP_A_AGENT_A_H

#include "engine/functions.h"

// Prototypes for functions defined in src/wip/A/ (Implementer A).
// Plain (unmangled) functions get C linkage here; the original debug names of mangled ones are C++.

extern "C" {
// Defined in this directory, not yet in engine/functions.h.
void BgInit(void);
void em0b_init(Entity *e);
int areacheck2(Entity *e);
void em16_getdir(Entity *e);
void kamen_init(Entity *e);
void em21_buttobi(Entity *e);
s32 WM_CheckInitialized(void);
void WM_DataSharingReceiveSlot(void *base, u32 index, void *src);

// Engine / Knife helpers called by these units (missing from engine/functions.h).
void func_02084828(Entity *e);
void *WmGetSharedDataAddress(void *base, u32 mask, void *shared, u32 index);
u32 MATH_CountPopulation(u32 value);
s32 WMi_CheckStateEx(u32 count, ...);
u32 WMi_SendCommandDirect(u16 *data, u32 count);
void WMi_SetCallbackTable(u32 id, void *table);
void WM_SetPortCallback(u32 port, u32 a, u32 b);
u32 WMi_SendCommand(u32 a, u32 b, ...);
void DC_InvalidateRange(void *addr, u32 size);
void DC_StoreRange(void *addr, u32 size);
void *func_0201eddc(void);
s32 NWMi_CheckInitialized(void);
void MIi_CpuCopy16(const void *src, void *dst, u32 size);
u32 OS_DisableInterrupts(void);
void OS_RestoreInterrupts(u32 state);
}

// C++ functions defined in this directory (mangled original names).
void cockpit_obj_set(u8 index);
void getdir(Entity *e);
u8 charMove(Entity *e, u8 mode);

// Data used by these units.
extern u8 data_0212c4a0[];
extern u8 data_0212c420[];
extern const u8 em2b_hitbox[];   // em2b_hitbox
extern const u8 em1c_charAnimTable[];   // em1c_charAnimTable
extern const u8 em16_timerTable[];   // em16_timerTable
extern const s8 getdir_offsetTable[];   // getdir_offsetTable
extern const u8 data_020d3224[];   // em27 hitbox
extern const u8 data_020ce4d0[];   // background init table
extern u16 data_0212c770;
extern u16 data_0212c77c;
extern u32 data_02134a68[];        // background animation slots (8 x 8 bytes)
extern u16 *data_02163fa4;
extern u16 *data_02158fa0;

#endif
