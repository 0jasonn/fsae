#include "engine/functions.h"
#include "global.h"
#include "types.h"

// subTask_init_obj_lang (0x0209c62c): copies the language-specific data block into a new buffer, opens it as a
// resource chunk and sends its object part. The block at data_0217a258 holds the source pointer and the buffer.

extern s32 data_0212c560;
extern u8 data_0217a258[];

extern "C" void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern "C" void DC_FlushRange(void *base, u32 size);
extern "C" s32 ResChunk_OpenRACH(void *entry, void *owner);
extern "C" void subTaskSendObjChar(void *buf, u32 offset, u32 size);
s32 _get_subtask_data_lang(s32 index);
s32 _get_subtask_data_size_lang(s32 index);

typedef struct SubtaskLangBlock {
    u8 unk_00[0x10];
    void *base;             // 0x10: source, then the new buffer
    void *obj;              // 0x14: the chunk object opened by ResChunk_OpenRACH
} SubtaskLangBlock;

typedef struct SubtaskChunkObj {
    u8 unk_00[0x10];
    u32 size;               // 0x10
    void *ptr;              // 0x14
} SubtaskChunkObj;

extern "C" void subTask_init_obj_lang(int a, int b);
void subTask_init_obj_lang(int a, int b) {
    SubtaskLangBlock *blk;
    SubtaskChunkObj *obj;
    s32 size;
    void *mem;

    if (a <= -1) {
        return;
    }
    blk = (SubtaskLangBlock *)data_0217a258;
    blk->base = (void *)(data_0212c560 + _get_subtask_data_lang(a));
    size = _get_subtask_data_size_lang(a);
    mem = EL_GetGlobalAdr(size, 0x20);
    MI_CpuCopy8(blk->base, mem, size);
    blk->base = mem;
    ResChunk_OpenRACH(mem, &blk->obj);
    obj = (SubtaskChunkObj *)blk->obj;
    DC_FlushRange(obj->ptr, obj->size);
    obj = (SubtaskChunkObj *)blk->obj;
    subTaskSendObjChar(obj->ptr, b, obj->size);
}
