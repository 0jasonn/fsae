#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/rect_f.h"

// rect_slot: functions RectItem_allocArray (0x020b8e28), RectObjList_findHit2 (0x020b8e88), RectSlot_status (0x020b8ef8)
// and RectSlot_init (0x020b8f0c), provisional names.

extern u8 data_02126ec0[];

// Item of a RectObj list (stride 0x18), see rect_item.cpp
typedef struct RectSlotItem {
    void *unk_00;      // 0x00
    void *unk_04;      // 0x04
    void *unk_08;      // 0x08
    void **block0c;    // 0x0c
    void **block10;    // 0x10
    u16 count;         // 0x14
} RectSlotItem;

// Slot record: a RectObjF base (vtable, offsets, size, bounds, flags) plus the fields used here
typedef struct RectSlot {
    void *vtable;      // 0x00 (data_02126ec0)
    s16 offsetX;       // 0x04
    s16 offsetY;       // 0x06
    s16 sizeX;         // 0x08
    s16 sizeY;         // 0x0a
    s16 boundX;        // 0x0c
    s16 boundY;        // 0x0e
    u8 flags;          // 0x10
    u8 unk_11[3];
    void *unk_14;      // 0x14
    u16 unk_18;        // 0x18
    u8 unk_1a[2];
    void *unk_1c;      // 0x1c
    s16 unk_20;        // 0x20
    s16 unk_22;        // 0x22
    s16 unk_24;        // 0x24
    s16 unk_26;        // 0x26
    s16 unk_28;        // 0x28
    s16 unk_2a;        // 0x2a
    s16 unk_2c;        // 0x2c
    s32 unk_30;        // 0x30
    u8 unk_34[4];
    s16 unk_38;        // 0x38
    s16 unk_3a;        // 0x3a
    u8 unk_3c;         // 0x3c
} RectSlot;

// RectItem_allocArray(holder, count) (0x020b8e28, provisional name): allocates count items (at least one) from the heap
// of holder, clears each one and returns the array, or NULL when the allocation fails
extern "C" RectSlotItem *RectItem_allocArray(void *holder, u32 count);
ARM RectSlotItem *RectItem_allocArray(void *holder, u32 count) {
    RectSlotItem *items;
    u32 i;
    u32 n;

    n = (count == 0) ? 1 : count;
    items = (RectSlotItem *)func_020c2c34(*(void **)holder, n * 0x18);
    if (items == NULL) {
        return NULL;
    }
    for (i = 0; i < count; i++) {
        RectSlotItem *item = &items[i];
        if (item != NULL) {
            RectItem_clear(item);
        }
    }
    return items;
}

// RectObjList_findHit2(items, count, pos) (0x020b8e88, provisional name): index of the first item that RectObj_hitTest
// accepts at pos, or -1 when none does (the same code as RectObjList_findHit)
extern "C" s32 RectObjList_findHit2(void **items, s32 count, s16 *pos);
ARM s32 RectObjList_findHit2(void **items, s32 count, s16 *pos) {
    s16 point[2];
    s16 i;

    for (i = 0; i < count; i++) {
        point[0] = pos[0];
        point[1] = pos[1];
        if (RectObj_hitTest(items[i], point) != FALSE) {
            return i;
        }
    }
    return -1;
}

// RectSlot_status(self) (0x020b8ef8, provisional name): -1 when the first word of self is set, otherwise 0
extern "C" s32 RectSlot_status(RectSlot *self);
ARM s32 RectSlot_status(RectSlot *self) {
    s32 status = 0;
    if (self->vtable != NULL) {
        status = -1;
    }
    return status;
}

// RectSlot_init(self) (0x020b8f0c, provisional name): RectObjLink2_init, then the vtable data_02126ec0, the offsets
// and flags of the slot (the two -1 halfwords at +0x2a and +0x2c, the byte at +0x3c set to 1). Returns self.
extern "C" void *RectSlot_init(RectSlot *self);
ARM void *RectSlot_init(RectSlot *self) {
    RectObjLink2_init(self);
    self->vtable = data_02126ec0;
    self->unk_1c = NULL;
    self->unk_20 = 0;
    self->unk_22 = 0;
    self->unk_24 = 0;
    self->unk_26 = 0;
    self->unk_28 = 0;
    self->unk_2a = -1;
    self->unk_2c = -1;
    self->unk_30 = 0;
    self->unk_38 = 0;
    self->unk_3a = 0;
    self->unk_3c = 1;
    return self;
}
