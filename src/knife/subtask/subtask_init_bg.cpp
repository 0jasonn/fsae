#include "engine/functions.h"
#include "knife/subtask/subtask_d.h"
#include "global.h"
#include "types.h"
#include "knife/subtask/subtask_init_bg.h"

// subTask_init_bg3 (0x0209c02c) and subTask_init_bg2 (0x0209c1d0): load the background chunks of the three
// subtask slots (a, b, c) for the language data at data_0212c55c. Each slot keeps its base (the loaded block) and its
// chunk object in the block: slot b at 0x00/0x04, slot a at 0x08/0x0c, slot c at 0x10/0x14.

extern u8 data_0217a318[];
extern u8 data_0217a2f8[];
extern void *data_0212c55c;

typedef struct SubtaskBgChunkBlock {
    void *bBase;     // 0x00
    void *bObj;      // 0x04
    void *aBase;     // 0x08
    void *aObj;      // 0x0c
    void *cBase;     // 0x10
    void *cObj;      // 0x14
} SubtaskBgChunkBlock;

extern "C" void subTask_init_bg3(int a, int b, int c);
void subTask_init_bg3(int a, int b, int c) {
    SubtaskBgChunkBlock *blk;
    SubtaskRachChunk *aObj;
    SubtaskNrcsChunk *obj;
    s32 size;
    void *mem;

    if (a > -1) {
        blk = (SubtaskBgChunkBlock *)data_0217a318;
        blk->aBase = (void *)((u8 *)data_0212c55c + _get_subtask_data(a));
        size = _get_subtask_data_size(a);
        mem = EL_GetGlobalAdr(size, 0x20);
        MI_CpuCopy8(blk->aBase, mem, size);
        blk->aBase = mem;
        ResChunk_OpenRACH2(mem, &blk->aObj);
        aObj = (SubtaskRachChunk *)blk->aObj;
        DC_FlushRange(aObj->ptr, aObj->size);
        aObj = (SubtaskRachChunk *)blk->aObj;
        subTaskSendBgChar(3, aObj->ptr, 0, aObj->size);
    }
    if (b > -1) {
        blk = (SubtaskBgChunkBlock *)data_0217a318;
        blk->bBase = (void *)((u8 *)data_0212c55c + _get_subtask_data(b));
        size = _get_subtask_data_size(b);
        mem = EL_GetGlobalAdr(size, 0x20);
        MI_CpuCopy8(blk->bBase, mem, size);
        blk->bBase = mem;
        DC_FlushRange(mem, size);
        ResChunk_OpenTTLP(blk->bBase, &blk->bObj);
        GXS_BeginLoadBGExtPltt();
        obj = (SubtaskNrcsChunk *)blk->bObj;
        GXS_LoadBGExtPltt(obj->ptr, 0x6000, obj->size);
        GXS_EndLoadBGExtPltt();
    }
    if (c > -1) {
        blk = (SubtaskBgChunkBlock *)data_0217a318;
        blk->cBase = (void *)((u8 *)data_0212c55c + _get_subtask_data(c));
        size = _get_subtask_data_size(c);
        mem = EL_GetGlobalAdr(size, 0x20);
        MI_CpuCopy8(blk->cBase, mem, size);
        blk->cBase = mem;
        ResChunk_GetNRCS(mem, &blk->cObj);
        obj = (SubtaskNrcsChunk *)blk->cObj;
        DC_FlushRange((u8 *)obj + 0xc, obj->size);
        obj = (SubtaskNrcsChunk *)blk->cObj;
        subTaskSendScr(3, (u8 *)obj + 0xc, 0, obj->size);
    }
}

extern "C" void subTask_init_bg2(int a, int b, int c);
void subTask_init_bg2(int a, int b, int c) {
    SubtaskBgChunkBlock *blk;
    SubtaskRachChunk *aObj;
    SubtaskNrcsChunk *obj;
    s32 size;
    void *mem;

    if (a > -1) {
        blk = (SubtaskBgChunkBlock *)data_0217a2f8;
        blk->aBase = (void *)((u8 *)data_0212c55c + _get_subtask_data(a));
        size = _get_subtask_data_size(a);
        mem = EL_GetGlobalAdr(size, 0x20);
        MI_CpuCopy8(blk->aBase, mem, size);
        blk->aBase = mem;
        ResChunk_OpenRACH2(mem, &blk->aObj);
        aObj = (SubtaskRachChunk *)blk->aObj;
        DC_FlushRange(aObj->ptr, aObj->size);
        aObj = (SubtaskRachChunk *)blk->aObj;
        subTaskSendBgChar(2, aObj->ptr, 0, aObj->size);
    }
    if (b > -1) {
        blk = (SubtaskBgChunkBlock *)data_0217a2f8;
        blk->bBase = (void *)((u8 *)data_0212c55c + _get_subtask_data(b));
        size = _get_subtask_data_size(b);
        mem = EL_GetGlobalAdr(size, 0x20);
        MI_CpuCopy8(blk->bBase, mem, size);
        blk->bBase = mem;
        ResChunk_OpenTTLP(blk->bBase, &blk->bObj);
        *(u16 *)((SubtaskNrcsChunk *)blk->bObj)->ptr = 0;
        DC_FlushRange(((SubtaskNrcsChunk *)blk->bObj)->ptr, 0x200);
        subTaskSendBgPlt(((SubtaskNrcsChunk *)blk->bObj)->ptr, 0, 0x200);
    }
    if (c > -1) {
        blk = (SubtaskBgChunkBlock *)data_0217a2f8;
        blk->cBase = (void *)((u8 *)data_0212c55c + _get_subtask_data(c));
        size = _get_subtask_data_size(c);
        mem = EL_GetGlobalAdr(size, 0x20);
        MI_CpuCopy8(blk->cBase, mem, size);
        blk->cBase = mem;
        ResChunk_GetNRCS(mem, &blk->cObj);
        obj = (SubtaskNrcsChunk *)blk->cObj;
        DC_FlushRange((u8 *)obj + 0xc, obj->size);
        obj = (SubtaskNrcsChunk *)blk->cObj;
        subTaskSendScr(2, (u8 *)obj + 0xc, 0, obj->size);
    }
}
