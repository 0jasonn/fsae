#include "engine/functions.h"
#include "global.h"

extern "C" s32 _ZN17groupSelectUIView7getTextEP12KnifeMsgTextml(void *self, void *text, u32 textId, s32 language);

// groupSelectUIView_getText_adjust (0x020b11cc): this-adjusting thunk (this - 0x30) of groupSelectUIView::getText for
// the secondary base. The compiler generates it for the virtual override; it is written as instructions because the
// vtable that would own it cannot be reproduced.
extern "C" asm s32 groupSelectUIView_getText_adjust(void *self, void *text, u32 textId, s32 language) {
    ldr ip, =-0x30
    add r0, r0, ip
    b _ZN17groupSelectUIView7getTextEP12KnifeMsgTextml
}
