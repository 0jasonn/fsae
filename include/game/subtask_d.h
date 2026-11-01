#ifndef WIP_D_SUBTASK_D_H
#define WIP_D_SUBTASK_D_H

#include "engine/functions.h"
#include "types.h"

// Calls into the rest of the image that engine/functions.h does not declare yet (plain names: extern "C").
extern "C" void *loadFile(u32 *size, const char *path, s32 align);
extern "C" void MI_UncompressLZ16(const void *src, void *dst);
extern "C" void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern "C" void MI_CpuFill8(void *dst, u8 value, u32 size);
extern "C" void DC_FlushRange(void *base, u32 size);
extern "C" void OS_EnableDTCM(void);
extern "C" s32 KnifeApp_getCurrentLanguage(void *app);

extern "C" s32 ResChunk_OpenRACH2(void *entry, void *owner);
extern "C" s32 ResChunk_OpenTTLP(void *entry, void *owner);
extern "C" s32 ResChunk_GetNRCS(void *entry, void *owner);
extern "C" void GXS_BeginLoadBGExtPltt(void);
extern "C" void GXS_LoadBGExtPltt(void *data, u32 offset, u32 size);
extern "C" void GXS_EndLoadBGExtPltt(void);
extern "C" void subTaskSendBgChar(s16 index, void *data, u32 offset, u32 size);
extern "C" void subTaskSendBgPlt(void *data, u32 offset, u32 size);
extern "C" s32 ResChunk_OpenKBEC(void *entry, void *owner);
extern "C" s32 ResChunk_OpenRACH(void *entry, void *owner);
extern "C" s32 Menu_ForwardC2cb4(void *entry, void *owner);
extern "C" void subTaskSendObjChar(void *data, u32 offset, u32 size);
extern "C" void subTaskSendObjPlt(void *data, u32 offset, u32 size);
extern "C" void Slots_ClearThree(void *block);
extern "C" void Slots_ClearThreeAt8(void *block);
// subTaskSendScr(short, void*, unsigned long, unsigned long) is C++ (mangled _Z14subTaskSendScrsPvmm).
void subTaskSendScr(s16 index, void *data, u32 offset, u32 size);
// _get_subtask_data(long) and _get_subtask_data_size(long) are C++ (mangled).
s32 _get_subtask_data(s32 index);
s32 _get_subtask_data_size(s32 index);

// InitOamManager(NNSG2dOamManagerInstance *) is C++ (mangled _Z14InitOamManagerP24NNSG2dOamManagerInstance).
struct NNSG2dOamManagerInstance;
void InitOamManager(NNSG2dOamManagerInstance *manager);

#endif
