#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Knife::Comm::InterruptDisabledSection::~InterruptDisabledSection (deleting dtor, 0x02093b00): restores the interrupt
// master enable (REG_IME) saved in the section at +0x04, then frees the block. The read of REG_IME is kept (volatile).

#define REG_IME (*(volatile u16 *)0x04000208)

extern char data_0211b0d4[]; // InterruptDisabledSection vtable (rodata)

extern "C" void *Knife_Comm_InterruptDisabledSection_dtor_InterruptDisabledSection_093b00(void *self);
ARM void *Knife_Comm_InterruptDisabledSection_dtor_InterruptDisabledSection_093b00(void *self) {
    *(void **)self = data_0211b0d4;
    (void)REG_IME;
    REG_IME = *(u32 *)((u8 *)self + 4);
    operator delete(self);
    return self;
}
