#include "engine/functions.h"
#include "global.h"
#include "types.h"

// rect_list_2: functions RectObjList_init (0x020b826c), RectObjList_init2 (0x020b829c) and RectObjList_setGeometry (0x020b82cc),
// all matching.

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
extern "C" void func_020bc2a8(void *owner, void *value, s32 kind);
extern "C" void func_020bc2d0(void *owner, void *value, s32 x, s32 y);
extern "C" void *func_020c2c34(void *heap, s32 size);
extern "C" void func_020c2c48(void *heap, void *block);

// RectObjList_init(self) (0x020b826c, provisional name): RectObj_init, the vtable data_02126dc4, the value -1 at
// +0x14 and a zero count. Returns self.
extern "C" void *RectObjList_init(RectObjList *self);
ARM void *RectObjList_init(RectObjList *self) {
    RectObj_init(self);
    self->vtable = data_02126dc4;
    self->field14 = (void *)-1;
    self->count = 0;
    return self;
}

// RectObjList_init2(self) (0x020b829c, provisional name): the same code as RectObjList_init
extern "C" void *RectObjList_init2(RectObjList *self);
ARM void *RectObjList_init2(RectObjList *self) {
    RectObj_init(self);
    self->vtable = data_02126dc4;
    self->field14 = (void *)-1;
    self->count = 0;
    return self;
}

// RectObjList_setGeometry(self, pos, size, value) (0x020b82cc, provisional name): the same code as
// RectObjLink_setGeometry
extern "C" void RectObjList_setGeometry(RectObjList *self, s16 *pos, s16 *size, s32 value);
ARM void RectObjList_setGeometry(RectObjList *self, s16 *pos, s16 *size, s32 value) {
    self->offsetX = pos[0];
    self->offsetY = pos[1];
    self->sizeX = size[0];
    self->sizeY = size[1];
    self->field14 = (void *)value;
}
