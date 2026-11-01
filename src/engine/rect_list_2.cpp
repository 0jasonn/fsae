#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/rect_list.h"

// rect_list_2: functions RectObjList_init (0x020b826c), RectObjList_init2 (0x020b829c) and RectObjList_setGeometry (0x020b82cc),
// all matching.

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

// RectObjList_init(self) (0x020b826c, provisional name): RectObj_init, the vtable data_02126dc4, the value -1 at
// +0x14 and a zero count. Returns self.
extern "C" void *RectObjList_init(RectObjList *self);
void *RectObjList_init(RectObjList *self) {
    RectObj_init(self);
    self->vtable = data_02126dc4;
    self->field14 = (void *)-1;
    self->count = 0;
    return self;
}

// RectObjList_init2(self) (0x020b829c, provisional name): the same code as RectObjList_init
extern "C" void *RectObjList_init2(RectObjList *self);
void *RectObjList_init2(RectObjList *self) {
    RectObj_init(self);
    self->vtable = data_02126dc4;
    self->field14 = (void *)-1;
    self->count = 0;
    return self;
}

// RectObjList_setGeometry(self, pos, size, value) (0x020b82cc, provisional name): the same code as
// RectObjLink_setGeometry
extern "C" void RectObjList_setGeometry(RectObjList *self, s16 *pos, s16 *size, s32 value);
void RectObjList_setGeometry(RectObjList *self, s16 *pos, s16 *size, s32 value) {
    self->offsetX = pos[0];
    self->offsetY = pos[1];
    self->sizeX = size[0];
    self->sizeY = size[1];
    self->field14 = (void *)value;
}
