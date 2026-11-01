#include "engine/functions.h"
#include "global.h"
#include "types.h"

// subTask_init_bg2_lang (0x0209c384): the background version of subTask_init_obj_lang. The block at data_0217a2f8 holds
// the source pointer (0x18) and the chunk object (0x1c); the chunk is sent as background character data (index 2).

extern s32 data_0212c560;
extern u8 data_0217a2f8[];

extern "C" void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern "C" void DC_FlushRange(void *base, u32 size);
extern "C" s32 ResChunk_OpenRACH2(void *entry, void *owner);
extern "C" void subTaskSendBgChar(s16 index, void *data, u32 offset, u32 size);
s32 _get_subtask_data_lang(s32 index);
s32 _get_subtask_data_size_lang(s32 index);

typedef struct SubtaskLangBgBlock {
    u8 unk_00[0x18];
    void *base;             // 0x18: source, then the new buffer
    void *obj;              // 0x1c: the chunk object opened by ResChunk_OpenRACH2
} SubtaskLangBgBlock;

typedef struct SubtaskBgChunkObj {
    u8 unk_00[0x10];
    u32 size;               // 0x10
    void *ptr;              // 0x14
} SubtaskBgChunkObj;

extern "C" void subTask_init_bg2_lang(int a, int b);
ARM void subTask_init_bg2_lang(int a, int b) {
    SubtaskLangBgBlock *blk;
    SubtaskBgChunkObj *obj;
    s32 size;
    void *mem;

    if (a <= -1) {
        return;
    }
    blk = (SubtaskLangBgBlock *)data_0217a2f8;
    blk->base = (void *)(data_0212c560 + _get_subtask_data_lang(a));
    size = _get_subtask_data_size_lang(a);
    mem = EL_GetGlobalAdr(size, 0x20);
    MI_CpuCopy8(blk->base, mem, size);
    blk->base = mem;
    ResChunk_OpenRACH2(mem, &blk->obj);
    obj = (SubtaskBgChunkObj *)blk->obj;
    DC_FlushRange(obj->ptr, obj->size);
    obj = (SubtaskBgChunkObj *)blk->obj;
    subTaskSendBgChar(2, obj->ptr, b, obj->size);
}
