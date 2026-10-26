#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/rect_obj_f.h"

// rect_item_2: functions RectItem_allocPtrArray (0x020b8b68), RectItem_allocPtrArray2 (0x020b8bb4), RectSpan_clear
// (0x020b8c00), RectSpan_freeItems (0x020b8c10), RectItem_freeArray (0x020b8c2c) and RectSpan_callAndMore (0x020b8c78).

// Item of a RectObjPair group (stride 0x18), see rect_item.cpp
typedef struct RectItem {
    void *unk_00;      // 0x00
    void *unk_04;      // 0x04
    void *unk_08;      // 0x08
    void **block0c;    // 0x0c
    void **block10;    // 0x10
    u16 count;         // 0x14
} RectItem;

// Span of items: the array and its count (count at +4)
typedef struct RectSpan {
    RectItem *items;   // 0x00
    u16 count;         // 0x04
} RectSpan;

extern "C" void RectItem_freeBlock(void *holder, void *block);
extern "C" void RectItem_releaseBlocks(RectItem *self, void *holder);
extern "C" void Heap_VirtualFree(void *heap, void *block);
extern "C" void *func_020c2c34(void *heap, s32 size);

// RectItem_allocPtrArray(holder, count) (0x020b8b68, provisional name): allocates count pointers (at least one) from
// the heap of holder and clears them. Returns NULL when the allocation fails.
extern "C" void **RectItem_allocPtrArray(void *holder, s32 count);
ARM void **RectItem_allocPtrArray(void *holder, s32 count) {
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

// RectItem_allocPtrArray2(holder, count) (0x020b8bb4, provisional name): the same code as RectItem_allocPtrArray
extern "C" void **RectItem_allocPtrArray2(void *holder, s32 count);
ARM void **RectItem_allocPtrArray2(void *holder, s32 count) {
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

// RectSpan_clear(self) (0x020b8c00, provisional name)
extern "C" void RectSpan_clear(RectSpan *self);
ARM void RectSpan_clear(RectSpan *self) {
    self->items = NULL;
    self->count = 0;
}

// RectSpan_freeItems(self, holder) (0x020b8c10, provisional name): frees the items of the span (tail call)
extern "C" void RectItem_freeArray(void *holder, RectItem *items, s32 count);
extern "C" void RectSpan_freeItems(RectSpan *self, void *holder);
ARM void RectSpan_freeItems(RectSpan *self, void *holder) {
    RectItem_freeArray(holder, self->items, self->count);
}

// RectItem_freeArray(holder, items, count) (0x020b8c2c, provisional name): releases the blocks of each item, then the
// array itself. Does nothing when items is NULL.
ARM void RectItem_freeArray(void *holder, RectItem *items, s32 count) {
    u32 i;

    if (items == NULL) {
        return;
    }
    for (i = 0; i < (u32)count; i++) {
        RectItem_releaseBlocks(&items[i], holder);
    }
    Heap_VirtualFree(*(void **)holder, items);
}

// RectSpan_callAndMore(self, arg, obj, value) (0x020b8c78, provisional name): calls slot 3 of obj with the tag
// 'cmtn' and arg, and when that returns a value, forwards it to func_020b8cbc with value
extern "C" s32 func_020b8cbc(RectSpan *self, void *result, s32 value);
extern "C" s32 RectSpan_callAndMore(RectSpan *self, void *arg, void *obj, s32 value);
ARM s32 RectSpan_callAndMore(RectSpan *self, void *arg, void *obj, s32 value) {
    s32 result;

    result = ((s32 (*)(void *, s32, void *))(((void **)(*(void **)obj))[3]))(obj, 0x6e746d63, arg);
    if (result == 0) {
        return 0;
    }
    return func_020b8cbc(self, (void *)result, value);
}
