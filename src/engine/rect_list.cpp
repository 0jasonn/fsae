#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/rect_list_api.h"
#include "engine/rect_list.h"

// rect_list: functions RectObjList_setItems (0x020b8078), RectObjList_allocPtrArray (0x020b80ec), RectObjList_releaseItems
// (0x020b8138) and RectObjList_freeBlock (0x020b8190), all matching.

// Calls through slot n of the vtable of an object (slot 0 is at +0)
typedef void (*RectSlotFn)(void *self, void *arg);
typedef void (*RectSlot3Fn)(void *self, void *arg, void *arg2);
#define RECT_SLOT(obj, n) (((RectSlotFn *)(*(void **)(obj)))[n])
#define RECT_SLOT3(obj, n) (((RectSlot3Fn *)(*(void **)(obj)))[n])

extern u8 data_02126dc4[];

extern "C" void RectObj_init(void *self);
extern "C" void RectObj_noop(void *self, void *arg);
extern "C" BOOL RectObj_updateBoundsCheck(void *self, s16 *pos);
extern "C" void Table_setValueB(void *owner, void *value, s32 kind);
extern "C" void RectBufTable_setup(void *owner, void *value, s32 x, s32 y);
extern "C" void *func_020c2c34(void *heap, s32 size);
extern "C" void Heap_VirtualFree(void *heap, void *block);

// RectObjList_setItems(self, holder, src, count, pos, size) (0x020b8078, provisional name): allocates the item array
// of count pointers, copies src into it, and sets the offset from pos and the size from size
extern "C" void RectObjList_setItems(RectObjList *self, void *holder, void **src, s32 count, s16 *pos, s16 *size);
void RectObjList_setItems(RectObjList *self, void *holder, void **src, s32 count, s16 *pos, s16 *size) {
    s32 i;

    self->field14 = RectObjList_allocPtrArray(holder, count);
    self->count = count;
    for (i = 0; i < count; i++) {
        ((void **)self->field14)[i] = src[i];
    }
    self->offsetX = pos[0];
    self->offsetY = pos[1];
    self->sizeX = size[0];
    self->sizeY = size[1];
}

// RectObjList_allocPtrArray(holder, count) (0x020b80ec, provisional name): allocates count pointers (at least one) from
// the heap of holder and clears them. Returns NULL when the allocation fails.
void **RectObjList_allocPtrArray(void *holder, s32 count) {
    void **array;
    void **slot;
    u32 i;

    array = (void **)func_020c2c34(*(void **)holder, (count == 0 ? 1 : count) << 2);
    if (array == NULL) {
        return NULL;
    }
    for (i = 0; i < (u32)count; i++) {
        slot = &array[i];
        if (slot != NULL) {
            *slot = NULL;
        }
    }
    return array;
}

// RectObjList_releaseItems(self, holder) (0x020b8138, provisional name): deletes every item, frees the array, then
// calls RectObj_noop
extern "C" void RectObjList_releaseItems(RectObjList *self, void *holder);
void RectObjList_releaseItems(RectObjList *self, void *holder) {
    s32 i;

    for (i = 0; i < self->count; i++) {
        func_020b81a8(holder, ((void **)self->field14)[i]);
    }
    RectObjList_freeBlock(holder, self->field14);
    RectObj_noop(self, holder);
}

// RectObjList_freeBlock(holder, block) (0x020b8190, provisional name): frees block when it is not NULL
void RectObjList_freeBlock(void *holder, void *block) {
    if (block == NULL) {
        return;
    }
    Heap_VirtualFree(*(void **)holder, block);
}
