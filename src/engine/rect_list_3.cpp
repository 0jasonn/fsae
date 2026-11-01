#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/rect_list.h"

// rect_list_3: function RectObjList_countDown (0x020b8384), matching.

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

// RectObjList_countDown(self) (0x020b8384, provisional name): decrements the count when it is not zero
extern "C" void RectObjList_countDown(RectObjList *self);
void RectObjList_countDown(RectObjList *self) {
    if (self->count != 0) {
        self->count = self->count - 1;
    }
}
