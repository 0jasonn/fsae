#include "engine/functions.h"
#include "global.h"
#include "types.h"

// ctrl_free_virtual: function Ctrl_freeVirtualBlock (0x020bc7b8), provisional name.

extern "C" void Heap_VirtualFree(void *heap, void *block);

// Block with one virtual slot: slot 0 is called with (block, holder). Declared only, never constructed, so no vtable
// is emitted here.
class CtrlVirtualBlock {
public:
    virtual void destroy(void *holder);
};

// Ctrl_freeVirtualBlock(holder, block) (0x020bc7b8, provisional name): does nothing for a NULL block; otherwise calls
// the first virtual of block with holder and frees the block from the heap at the first word of holder
extern "C" void Ctrl_freeVirtualBlock(void *holder, void *block);
ARM void Ctrl_freeVirtualBlock(void *holder, void *block) {
    if (block == NULL) {
        return;
    }
    ((CtrlVirtualBlock *)block)->destroy(holder);
    Heap_VirtualFree(*(void **)holder, block);
}
