#ifndef WIP_B_EXTRA_H
#define WIP_B_EXTRA_H

#include "engine/entity.h"

// Functions used by the B files that engine/functions.h and game/*.h do not declare yet
// (reviewer: move them to functions.h).
void ZeldaFadeSet(Entity *e, u32 mode);     // ZeldaFadeSet(OBJ_WORK_*, unsigned long), 0x0205b67c
s8 ReadCartInfo(u32 *data);                 // ReadCartInfo(unsigned long*), 0x02056188 (src/game/backup.cpp)
s32 Knife_writeHeaderBlock(const u32 *data); // 0x02056174 (src/game/backup.cpp)

extern "C" void OS_GetOwnerInfoEx(void *info); // 0x020198e4, TwlSDK (unmangled)

extern "C" void DC_FlushRange(void *base, u32 size);            // 0x020184b8, TwlSDK
extern "C" void GXx_SetMasterBrightness_(void *reg, u32 value); // 0x02012f70, TwlSDK

#endif
