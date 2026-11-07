#include "engine/functions.h"
#include "global.h"

extern "C" s32 nameEntryUIView_getText(void *self, void *text, u32 textId, s32 language);

// nameEntryUIView_getText_adjust (0x020afc60): this-adjusting thunk (this - 0x30) of getText for the secondary base.
// The compiler generates it for the virtual override; it is written as instructions because the vtable that would
// own it cannot be reproduced.
extern "C" asm s32 nameEntryUIView_getText_adjust(void *self, void *text, u32 textId, s32 language) {
    ldr ip, =-0x30
    add r0, r0, ip
    b nameEntryUIView_getText
}
