#include "engine/functions.h"
#include "global.h"
#include "types.h"

// rect_list_4: functions Group_allocU16Array (0x020b9284), Group_allocU32Array (0x020b92d0), Group_release (0x020b931c),
// Group_freeBlock (0x020b9350) and Group_freeBlock2 (0x020b9368), all matching.

// Group with two heap blocks at +0x30 and +0x34 and the list at +0x14 (see rect_list.cpp)
typedef struct RectGroup {
    u8 unk_00[0x30];
    void *block30;     // 0x30
    void *block34;     // 0x34
} RectGroup;

extern "C" void *func_020c2c34(void *heap, s32 size);
extern "C" void func_020c2c48(void *heap, void *block);
extern "C" void RectObjList_releaseItems(void *self, void *holder);
extern "C" void Group_freeBlock(void *holder, void *block);
extern "C" void Group_freeBlock2(void *holder, void *block);

// Group_allocU16Array(holder, count) (0x020b9284, provisional name): allocates count halfwords (at least one) from the
// heap of holder and clears them. Returns NULL when the allocation fails.
extern "C" u16 *Group_allocU16Array(void *holder, s32 count);
ARM u16 *Group_allocU16Array(void *holder, s32 count) {
    u16 *array;
    u16 *slot;
    u32 i;

    array = (u16 *)func_020c2c34(*(void **)holder, (count == 0 ? 1 : count) << 1);
    if (array == NULL) {
        return NULL;
    }
    for (i = 0; i < (u32)count; i++) {
        slot = &array[i];
        if (slot != NULL) {
            *slot = 0;
        }
    }
    return array;
}

// Group_allocU32Array(holder, count) (0x020b92d0, provisional name): allocates count words (at least one) from the
// heap of holder and clears them. Returns NULL when the allocation fails.
extern "C" u32 *Group_allocU32Array(void *holder, s32 count);
ARM u32 *Group_allocU32Array(void *holder, s32 count) {
    u32 *array;
    u32 *slot;
    u32 i;

    array = (u32 *)func_020c2c34(*(void **)holder, (count == 0 ? 1 : count) << 2);
    if (array == NULL) {
        return NULL;
    }
    for (i = 0; i < (u32)count; i++) {
        slot = &array[i];
        if (slot != NULL) {
            *slot = 0;
        }
    }
    return array;
}

// Group_release(self, holder) (0x020b931c, provisional name): frees the two blocks, then releases the list
extern "C" void Group_release(RectGroup *self, void *holder);
ARM void Group_release(RectGroup *self, void *holder) {
    Group_freeBlock2(holder, self->block34);
    Group_freeBlock(holder, self->block30);
    RectObjList_releaseItems(self, holder);
}

// Group_freeBlock(holder, block) (0x020b9350, provisional name): frees block when it is not NULL
ARM void Group_freeBlock(void *holder, void *block) {
    if (block == NULL) {
        return;
    }
    func_020c2c48(*(void **)holder, block);
}

// Group_freeBlock2(holder, block) (0x020b9368, provisional name): the same code as Group_freeBlock
ARM void Group_freeBlock2(void *holder, void *block) {
    if (block == NULL) {
        return;
    }
    func_020c2c48(*(void **)holder, block);
}
