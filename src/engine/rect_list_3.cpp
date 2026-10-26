#include "engine/functions.h"
#include "global.h"
#include "types.h"

// rect_list_3: function RectObjList_countDown (0x020b8384), matching.

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

// RectObjList_countDown(self) (0x020b8384, provisional name): decrements the count when it is not zero
extern "C" void RectObjList_countDown(RectObjList *self);
ARM void RectObjList_countDown(RectObjList *self) {
    if (self->count != 0) {
        self->count = self->count - 1;
    }
}
