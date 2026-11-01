#ifndef WIP_D_WM_IRQ_H
#define WIP_D_WM_IRQ_H

#include "types.h"

// Stack copy of the Knife::Comm::InterruptDisabledSection the WirelessManager functions declare: the vtable (data_0211b0d4)
// at +0 and the REG_IME value saved at +4. Written out by hand (no constructor or destructor), so no out-of-line copy of the
// class is emitted into the object.
extern char data_0211b0d4[];

typedef struct WmIrqGuard {
    void *volatile vtbl;     // volatile: the stores to it are kept (the original never reads it back)
    u32 savedIme;
} WmIrqGuard;

#endif
