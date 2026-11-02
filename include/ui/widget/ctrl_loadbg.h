#ifndef WIP_F_CTRL_LOADBG_H
#define WIP_F_CTRL_LOADBG_H

// Declarations for the background resource loader of implementer F (round 16). The helpers it calls are declared here
// with the signatures their call sites use; the reviewer checks them against their own units.

#include "engine/functions.h"
#include "types.h"

extern "C" {
u8 OS_getOwnerFlag(void);
s32 func_0201dc94(void *dst, s32 size, const u8 *format, ...);
void Ctrl_findEntryD(void *out, const void *name);
void Ctrl_findEntryC(void *out, const void *name);
void Ctrl_findEntryE(void *out, const void *name);
void Slots_ClearThreeAt8(void *block);
void func_020c3dac(s32 handle, s32 a, s32 b, void *block);
void BgLoad_Resources(s32 index, s32 a, s32 b, s32 c, s32 d, s32 e);
void Ctrl_loadBgResources(void);
}

#endif
