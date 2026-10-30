#include "engine/functions.h"
#include "global.h"
#include "types.h"

// ctrl_free_2: function Ctrl_freeSpanBlock (0x020bc7ec), provisional name.

extern "C" void Heap_VirtualFree(void *heap, void *block);
extern "C" void RectSpan_freeItems(void *self, void *holder);

// Ctrl_freeSpanBlock(holder, block) (0x020bc7ec, provisional name): does nothing for a NULL block; otherwise frees the
// items of block with RectSpan_freeItems(block, holder) and frees the block from the heap at the first word of holder
extern "C" void Ctrl_freeSpanBlock(void *holder, void *block);
ARM void Ctrl_freeSpanBlock(void *holder, void *block) {
    if (block == NULL) {
        return;
    }
    RectSpan_freeItems(block, holder);
    Heap_VirtualFree(*(void **)holder, block);
}
