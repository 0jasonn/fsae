#ifndef WIP_D_WM_GUARD_H
#define WIP_D_WM_GUARD_H

#include "types.h"
#include "knife/comm/wm_work.h"  // WM_REG_IME
#include "knife/comm/wm_irq.h"   // WmIrqGuard (vtable word + saved REG_IME), data_0211b0d4

// The WirelessManager functions run with REG_IME cleared. The original builds an InterruptDisabledSection on the stack
// (vtable word data_0211b0d4 at +0, the saved REG_IME at +4); its destructor restores REG_IME on every exit. Written out
// as macros here, so no constructor or destructor (and no out-of-line copy of one) is emitted into the object.
//
// WM_IRQ_ENTER(guard, saved): saves REG_IME into `saved` (a u16 local), clears it, stores the vtable word and the saved value.
// WM_IRQ_LEAVE(guard): before every return: reads REG_IME, stores the vtable word again, restores REG_IME.

#define WM_IRQ_ENTER(guard, saved) \
    do { \
        (saved) = WM_REG_IME; \
        WM_REG_IME = 0; \
        (guard).vtbl = data_0211b0d4; \
        (guard).savedIme = (saved); \
    } while (0)

#define WM_IRQ_LEAVE(guard) \
    do { \
        (void)WM_REG_IME; \
        (guard).vtbl = data_0211b0d4; \
        WM_REG_IME = (u16)(guard).savedIme; \
    } while (0)

#endif
