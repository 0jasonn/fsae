#include "engine/functions.h"
#include "game/subtask_d.h"
#include "global.h"
#include "types.h"
#include "game/subtask_init_bg.h"

// subTask_init_obj(int, int, int, int) (0x0209c41c): switches the sub display control register (0x04001000) to the
// subtask layout, then for each of the four slots (c, d, a, b, in that code order) with an index above -1 loads its
// data block into data_0217a258 and opens the chunk object of its kind. Finally it clears the two slot tables.

extern u8 data_0217a258[];
extern void *data_0212c55c;

typedef struct SubtaskObjBlock {
    void *bBase;     // 0x00
    void *bObj;      // 0x04
    void *aBase;     // 0x08
    void *aObj;      // 0x0c
    u8 unk_10[0x8];
    void *cBase;     // 0x18
    void *cObj;      // 0x1c
    void *dBase;     // 0x20
    void *dObj;      // 0x24
    u8 unk_28[0x24]; // 0x28: cleared by Slots_ClearThree
} SubtaskObjBlock;

void subTask_init_obj(int a, int b, int c, int d) {
    SubtaskObjBlock *blk;
    SubtaskRachChunk *aObj;
    SubtaskNrcsChunk *obj;
    s32 size;
    void *mem;
    u32 *dispcnt;

    dispcnt = (u32 *)0x04001000;
    *dispcnt = *dispcnt & 0xffcfffef;
    blk = (SubtaskObjBlock *)data_0217a258;
    if (c > -1) {
        blk->cBase = (void *)((u8 *)data_0212c55c + _get_subtask_data(c));
        size = _get_subtask_data_size(c);
        mem = EL_GetGlobalAdr(size, 0x20);
        MI_CpuCopy8(blk->cBase, mem, size);
        blk->cBase = mem;
        DC_FlushRange(mem, size);
        ResChunk_OpenKBEC(blk->cBase, &blk->cObj);
    }
    if (d > -1) {
        blk->dBase = (void *)((u8 *)data_0212c55c + _get_subtask_data(d));
        size = _get_subtask_data_size(d);
        mem = EL_GetGlobalAdr(size, 0x20);
        MI_CpuCopy8(blk->dBase, mem, size);
        blk->dBase = mem;
        DC_FlushRange(mem, size);
        Menu_ForwardC2cb4(blk->dBase, &blk->dObj);
    }
    if (a > -1) {
        blk->aBase = (void *)((u8 *)data_0212c55c + _get_subtask_data(a));
        size = _get_subtask_data_size(a);
        mem = EL_GetGlobalAdr(size, 0x20);
        MI_CpuCopy8(blk->aBase, mem, size);
        blk->aBase = mem;
        ResChunk_OpenRACH(mem, &blk->aObj);
        aObj = (SubtaskRachChunk *)blk->aObj;
        DC_FlushRange(aObj->ptr, aObj->size);
        aObj = (SubtaskRachChunk *)blk->aObj;
        subTaskSendObjChar(aObj->ptr, 0, aObj->size);
    }
    if (b > -1) {
        blk->bBase = (void *)((u8 *)data_0212c55c + _get_subtask_data(b));
        size = _get_subtask_data_size(b);
        mem = EL_GetGlobalAdr(size, 0x20);
        MI_CpuCopy8(blk->bBase, mem, size);
        blk->bBase = mem;
        ResChunk_OpenTTLP(mem, &blk->bObj);
        obj = (SubtaskNrcsChunk *)blk->bObj;
        DC_FlushRange(obj->ptr, obj->size);
        obj = (SubtaskNrcsChunk *)blk->bObj;
        subTaskSendObjPlt(obj->ptr, 0, obj->size);
    }
    Slots_ClearThree((u8 *)blk + 0x28);
    Slots_ClearThreeAt8((u8 *)blk + 0x4c);
}
