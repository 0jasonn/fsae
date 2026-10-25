#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/pane.h"

// pane_f.cpp: functions Window_allocItems (0x020b5c58), PaneItem_allocArray (0x020b5c84), Window_release (0x020b5cd4),
// Window_releaseItems (0x020b5d00), all matching.

extern "C" void Pane_releaseChildren(Pane *self, void *heap);
extern "C" void Pane_releaseItemNoop(void *item, void *heap);
extern "C" void Window_releaseItems(void *heap, PaneItem *items, u32 count);

// Window_allocItems(self, owner, count) (0x020b5c58, provisional name): allocates the item array of the window
extern "C" PaneItem *PaneItem_allocArray(void *owner, s32 count);
extern "C" void Window_allocItems(Pane *self, void *owner, s32 count);
ARM void Window_allocItems(Pane *self, void *owner, s32 count) {
    self->itemCount = 0;
    self->items = PaneItem_allocArray(owner, count);
    self->itemCount = count;
}

// PaneItem_allocArray(owner, count) (0x020b5c84, provisional name): allocates count items (at least one) and clears
// them. Returns NULL when the allocation fails.
ARM PaneItem *PaneItem_allocArray(void *owner, s32 count) {
    PaneItem *array;
    PaneItem *slot;
    u32 i;

    array = (PaneItem *)func_020c2c34(*(void **)owner, (count == 0 ? 1 : count) << 3);
    if (array == NULL) {
        return NULL;
    }
    for (i = 0; i < (u32)count; i++) {
        slot = &array[i];
        if (slot != NULL) {
            slot->source = NULL;
            slot->kind = 0;
        }
    }
    return array;
}

// Window_release(self, heap) (0x020b5cd4, provisional name): vtable slot 1 of Window, releases the items and the children
extern "C" void Window_release(Pane *self, void *heap);
ARM void Window_release(Pane *self, void *heap) {
    Window_releaseItems(heap, (PaneItem *)self->items, self->itemCount);
    Pane_releaseChildren(self, heap);
}

// Window_releaseItems(heap, items, count) (0x020b5d00, provisional name): calls the release callback on every item,
// then frees the array through the allocator of heap
ARM void Window_releaseItems(void *heap, PaneItem *items, u32 count) {
    u32 i;

    if (items == NULL) {
        return;
    }
    for (i = 0; i < count; i++) {
        Pane_releaseItemNoop(&items[i], heap);
    }
    func_020c2c48(*(void **)heap, items);
}
