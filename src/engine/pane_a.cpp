#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/pane.h"

// pane_a: functions Pane_init, Pane_initFromSpec, Pane_clearLinks, Pane_releaseChildren, Pane_freeBlock, Pane_allocChildren, Pane_allocPtrArray, Pane_appendChild (0x020b5578 to 0x020b5728), all matching.

// Pane_init(self, spec, ctx) (0x020b5578, provisional name): base constructor of the panes. Sets the vtable of Pane,
// clears the rectangle and copies the position and the size from spec
extern "C" void Pane_clearLinks(Pane *self);
extern "C" Pane *Pane_init(Pane *self, const PaneSpec *spec, void *ctx);
ARM Pane *Pane_init(Pane *self, const PaneSpec *spec, void *ctx) {
    self->vtable = data_02126a88;
    self->posX = 0;
    self->posY = 0;
    self->ofsX = 0;
    self->ofsY = 0;
    self->sizeX = 0;
    self->sizeY = 0;
    Pane_clearLinks(self);
    self->posX = spec->x;
    self->posY = spec->y;
    self->sizeX = spec->w;
    self->sizeY = spec->h;
    return self;
}

// Pane_initFromSpec(self, spec, ctx) (0x020b55d8, provisional name): same code as Pane_init, used by Pane_create
ARM Pane *Pane_initFromSpec(Pane *self, const PaneSpec *spec, void *ctx) {
    self->vtable = data_02126a88;
    self->posX = 0;
    self->posY = 0;
    self->ofsX = 0;
    self->ofsY = 0;
    self->sizeX = 0;
    self->sizeY = 0;
    Pane_clearLinks(self);
    self->posX = spec->x;
    self->posY = spec->y;
    self->sizeX = spec->w;
    self->sizeY = spec->h;
    return self;
}

// Pane_clearLinks(self) (0x020b5638, provisional name): clears the parent, the child array, the counts and flag 0x1c
ARM void Pane_clearLinks(Pane *self) {
    self->flag1c = 0;
    self->parent = NULL;
    self->children = NULL;
    self->childCount = 0;
    self->childCapacity = 0;
}

// Pane_releaseChildren(self, heap) (0x020b5654, provisional name): releases every child object, then the child array
extern "C" void Pane_freeBlock(void *heap, void *block);
extern "C" void Pane_releaseChildren(Pane *self, void *heap);
ARM void Pane_releaseChildren(Pane *self, void *heap) {
    s32 i;

    for (i = 0; i < self->childCount; i++) {
        lobby_releaseObj(heap, self->children[i]);
    }
    Pane_freeBlock(heap, self->children);
}

// Pane_freeBlock(heap, block) (0x020b56a0, provisional name): frees the block through the allocator, when it is not NULL
ARM void Pane_freeBlock(void *heap, void *block) {
    if (block == NULL) {
        return;
    }
    Heap_VirtualFree(*(void **)heap, block);
}

// Pane_allocChildren(self, owner, capacity) (0x020b56b8, provisional name): allocates the child array and stores the capacity
extern "C" void **Pane_allocPtrArray(void *owner, s32 count);
extern "C" void Pane_allocChildren(Pane *self, void *owner, s32 capacity);
ARM void Pane_allocChildren(Pane *self, void *owner, s32 capacity) {
    self->children = (Pane **)Pane_allocPtrArray(owner, capacity);
    self->childCapacity = capacity;
}

// Pane_allocPtrArray(owner, count) (0x020b56dc, provisional name): allocates count pointers (at least one) from the
// allocator of owner and clears them. Returns NULL when the allocation fails.
ARM void **Pane_allocPtrArray(void *owner, s32 count) {
    void **array;
    void **slot;
    u32 i;

    array = (void **)func_020c2c34(*(void **)owner, (count == 0 ? 1 : count) << 2);
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

// Pane_appendChild(self, child) (0x020b5728, provisional name): stores child at the end of the child array
extern "C" void Pane_appendChild(Pane *self, Pane *child);
ARM void Pane_appendChild(Pane *self, Pane *child) {
    u16 index;

    index = self->childCount;
    self->childCount = index + 1;
    self->children[index] = child;
    child->parent = self;
}
