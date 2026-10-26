#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/rect_obj_f.h"

// rect_item: functions RectObjPair_setOffsets (0x020b88dc), RectObjPair_setValue (0x020b895c),
// RectObjPair_updateChildren (0x020b8964), RectItem_clear (0x020b89e4), RectItem_releaseBlocks (0x020b8a04),
// RectItem_freeBlock (0x020b8a2c) and RectItem_freeBlock2 (0x020b8a44), all matching.

// Calls through slot n of the vtable of an object (slot 0 is at +0)
typedef void (*RectSlotFn)(void *self, void *arg);
#define RECT_SLOT(obj, n) (((RectSlotFn *)(*(void **)(obj)))[n])

// Item of a RectObjPair group (stride 0x18): three pointers, two heap blocks and a count
typedef struct RectItem {
    void *unk_00;      // 0x00
    void *unk_04;      // 0x04
    void *unk_08;      // 0x08
    void **block0c;   // 0x0c: pointer array, freed by RectItem_releaseBlocks
    void **block10;   // 0x10: pointer array, freed by RectItem_releaseBlocks
    u16 count;        // 0x14
} RectItem;

// Pair of RectObj children with a value and a limit (the children are RectObjF pointers at +0x14)
typedef struct RectObjPair {
    u8 unk_00[0x14];
    RectObjF **children;  // 0x14: two children
    u8 unk_18[2];
    s16 limit;            // 0x1a
    s16 offset;           // 0x1c
    s16 value;            // 0x1e
} RectObjPair;

extern "C" void RectObjLink_callB(RectObjF *self, void *arg);
extern "C" void Heap_VirtualFree(void *heap, void *block);

// RectObjPair_setOffsets(self, value) (0x020b88dc, provisional name): the first child moves to -value / 2 + 6 and
// the second to value - value / 2 - 6 (both through the offset slot of the child)
extern "C" void RectObjPair_setOffsets(RectObjPair *self, s32 value);
ARM void RectObjPair_setOffsets(RectObjPair *self, s32 value) {
    s16 offsets[2];
    s16 pos[2];
    s32 i;
    RectObjF *child;

    offsets[0] = -value / 2 + 6;
    offsets[1] = value - value / 2 - 6;
    for (i = 0; i < 2; i++) {
        pos[0] = self->children[i]->offsetX;
        pos[1] = offsets[i];
        RECT_SLOT(self->children[i], 2)(self->children[i], pos);
    }
}

// RectObjPair_setValue(self, value) (0x020b895c, provisional name)
extern "C" void RectObjPair_setValue(RectObjPair *self, s16 value);
ARM void RectObjPair_setValue(RectObjPair *self, s16 value) {
    self->value = value;
}

// RectObjPair_updateChildren(self, arg) (0x020b8964, provisional name): updates both children with arg, then sets
// the enable flag of the first child from value > 0 and of the second from value + offset < limit
extern "C" void RectObjPair_updateChildren(RectObjPair *self, void *arg);
ARM void RectObjPair_updateChildren(RectObjPair *self, void *arg) {
    RectObjF *child0;
    RectObjF *child1;

    RectObjLink_callB(self->children[0], arg);
    RectObjLink_callB(self->children[1], arg);
    s32 flag;

    flag = (self->value > 0) ? 1 : 0;
    RECT_SLOT(self->children[0], 4)(self->children[0], (void *)flag);
    flag = (self->value + self->offset < self->limit) ? 1 : 0;
    RECT_SLOT(self->children[1], 4)(self->children[1], (void *)flag);
}

// RectItem_clear(self) (0x020b89e4, provisional name): all pointers and the count to zero
extern "C" void RectItem_clear(RectItem *self);
ARM void RectItem_clear(RectItem *self) {
    self->unk_00 = NULL;
    self->unk_04 = NULL;
    self->unk_08 = NULL;
    self->block0c = NULL;
    self->block10 = NULL;
    self->count = 0;
}

// RectItem_releaseBlocks(self, holder) (0x020b8a04, provisional name): frees both pointer arrays of the item
extern "C" void RectItem_freeBlock(void *holder, void *block);
extern "C" void RectItem_freeBlock2(void *holder, void *block);
extern "C" void RectItem_releaseBlocks(RectItem *self, void *holder);
ARM void RectItem_releaseBlocks(RectItem *self, void *holder) {
    RectItem_freeBlock2(holder, self->block0c);
    RectItem_freeBlock(holder, self->block10);
}

// RectItem_freeBlock(holder, block) (0x020b8a2c, provisional name): frees block when it is not NULL
ARM void RectItem_freeBlock(void *holder, void *block) {
    if (block == NULL) {
        return;
    }
    Heap_VirtualFree(*(void **)holder, block);
}

// RectItem_freeBlock2(holder, block) (0x020b8a44, provisional name): the same code as RectItem_freeBlock
ARM void RectItem_freeBlock2(void *holder, void *block) {
    if (block == NULL) {
        return;
    }
    Heap_VirtualFree(*(void **)holder, block);
}
