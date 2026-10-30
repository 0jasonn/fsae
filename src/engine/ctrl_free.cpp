#include "engine/functions.h"
#include "global.h"
#include "types.h"

// ctrl_free: functions Ctrl_freeBlock (0x020bc78c) and Ctrl_freeVirtualBlock (0x020bc7b8), provisional names.

extern "C" void Heap_VirtualFree(void *heap, void *block);
// Ctrl_noopA is declared with no parameters in src/engine/ctrl_leaf.cpp; the call here passes (block, holder) and it ignores them
extern "C" void Ctrl_noopA(void *block, void *holder);

// Holder of a block: the heap pointer is the first word
typedef void (*CtrlBlockFn)(void *block, void *holder);
#define CTRL_BLOCK_SLOT0(obj) (((CtrlBlockFn *)(*(void **)(obj)))[0])

// Ctrl_freeBlock(holder, block) (0x020bc78c, provisional name): does nothing for a NULL block; otherwise calls the
// hook Ctrl_noopA with (block, holder) and frees the block from the heap at the first word of holder
extern "C" void Ctrl_freeBlock(void *holder, void *block);
ARM void Ctrl_freeBlock(void *holder, void *block) {
    if (block == NULL) {
        return;
    }
    Ctrl_noopA(block, holder);
    Heap_VirtualFree(*(void **)holder, block);
}
