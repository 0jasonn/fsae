#include "engine/functions.h"
#include "global.h"
#include "types.h"

// ctrl_free_virtual_2: function Ctrl_freeVirtualBlockB (0x020bc818), provisional name, the same code as Ctrl_freeVirtualBlock.

extern "C" void Heap_VirtualFree(void *heap, void *block);

// Block with one virtual slot: slot 0 is called with (block, holder). Declared only, never constructed, so no vtable
// is emitted here.
class CtrlVirtualBlockB {
public:
    virtual void destroy(void *holder);
};

// Ctrl_freeVirtualBlockB(holder, block) (0x020bc818, provisional name): does nothing for a NULL block; otherwise calls
// the first virtual of block with holder and frees the block from the heap at the first word of holder
extern "C" void Ctrl_freeVirtualBlockB(void *holder, void *block);
ARM void Ctrl_freeVirtualBlockB(void *holder, void *block) {
    if (block == NULL) {
        return;
    }
    ((CtrlVirtualBlockB *)block)->destroy(holder);
    Heap_VirtualFree(*(void **)holder, block);
}
