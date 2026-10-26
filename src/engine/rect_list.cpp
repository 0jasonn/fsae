#include "engine/functions.h"
#include "global.h"
#include "types.h"

// rect_list: functions RectObjList_setItems (0x020b8078), RectObjList_allocPtrArray (0x020b80ec), RectObjList_releaseItems
// (0x020b8138) and RectObjList_freeBlock (0x020b8190), all matching.

// Calls through slot n of the vtable of an object (slot 0 is at +0)
typedef void (*RectSlotFn)(void *self, void *arg);
typedef void (*RectSlot3Fn)(void *self, void *arg, void *arg2);
#define RECT_SLOT(obj, n) (((RectSlotFn *)(*(void **)(obj)))[n])
#define RECT_SLOT3(obj, n) (((RectSlot3Fn *)(*(void **)(obj)))[n])

// List of RectObj children: the rectangle (offset, size, bounds), flags at +0x10, the item array (or a value) at +0x14
// and the count at +0x18
typedef struct RectObjList {
    void *vtable;      // 0x00 (data_02126dc4)
    s16 offsetX;       // 0x04
    s16 offsetY;       // 0x06
    s16 sizeX;         // 0x08
    s16 sizeY;         // 0x0a
    s16 boundX;        // 0x0c
    s16 boundY;        // 0x0e
    u8 flags;          // 0x10: bit 0 freezes the bounds, bits 1 and 2 choose the kind in updateAndCall
    u8 unk_11[3];
    void *field14;     // 0x14: item array, or a value
    u16 count;         // 0x18
} RectObjList;

extern u8 data_02126dc4[];

extern "C" void RectObj_init(void *self);
extern "C" void RectObj_noop(void *self, void *arg);
extern "C" BOOL RectObj_updateBoundsCheck(void *self, s16 *pos);
extern "C" void Table_setValueB(void *owner, void *value, s32 kind);
extern "C" void func_020bc2d0(void *owner, void *value, s32 x, s32 y);
extern "C" void *func_020c2c34(void *heap, s32 size);
extern "C" void func_020c2c48(void *heap, void *block);
extern "C" void **RectObjList_allocPtrArray(void *holder, s32 count);
extern "C" void RectObjList_freeBlock(void *holder, void *block);

// RectObjList_setItems(self, holder, src, count, pos, size) (0x020b8078, provisional name): allocates the item array
// of count pointers, copies src into it, and sets the offset from pos and the size from size
extern "C" void RectObjList_setItems(RectObjList *self, void *holder, void **src, s32 count, s16 *pos, s16 *size);
ARM void RectObjList_setItems(RectObjList *self, void *holder, void **src, s32 count, s16 *pos, s16 *size) {
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
ARM void **RectObjList_allocPtrArray(void *holder, s32 count) {
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
extern "C" void func_020b81a8(void *holder, void *obj);
extern "C" void RectObjList_releaseItems(RectObjList *self, void *holder);
ARM void RectObjList_releaseItems(RectObjList *self, void *holder) {
    s32 i;

    for (i = 0; i < self->count; i++) {
        func_020b81a8(holder, ((void **)self->field14)[i]);
    }
    RectObjList_freeBlock(holder, self->field14);
    RectObj_noop(self, holder);
}

// RectObjList_freeBlock(holder, block) (0x020b8190, provisional name): frees block when it is not NULL
ARM void RectObjList_freeBlock(void *holder, void *block) {
    if (block == NULL) {
        return;
    }
    func_020c2c48(*(void **)holder, block);
}
