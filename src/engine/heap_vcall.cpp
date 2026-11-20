#include "engine/functions.h"
#include "global.h"
#include "engine/heap_vcall.h"

// Heap_VirtualFree (Heap_VirtualFree, provisional name): calls slot 1 of the heap object's vtable with the block.
void Heap_VirtualFree(void *heap, void *block) {
    void **vtable;

    vtable = *(void ***)heap;
    ((void (*)(void *, void *))vtable[1])(heap, block);
}
