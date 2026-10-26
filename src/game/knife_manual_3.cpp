#include "engine/functions.h"
#include "global.h"
#include "game/g_knife_manual.h"

// Functions in this file (original names from the debug build):
//   Knife::i_deallocate (0x020c8094), Knife::i_VBlankIntr_OnManual (0x020c80b0), Knife_IrqStub (0x020c8100, empty IRQ stub)

namespace Knife {

// Knife::i_deallocate(void*) (0x020c8094): frees a block through the heap at data_02187050
ARM void i_deallocate(void *block) {
    if (block != 0) {
        Heap_VirtualFree(data_02187050, block);
    }
}

// Knife::i_VBlankIntr_OnManual() (0x020c80b0): saves the context, sets bit 0 of the register at 0x02fe3ff8,
// restores the context and waits until the divider is idle
ARM void i_VBlankIntr_OnManual(void) {
    u8 context[0x1c];

    u32 base;

    CP_SaveContext(context);
    base = (u32)data_02fe0000;
    base += 0x3000;
    *(u32 *)(base + 0xff8) |= 1;
    CPi_RestoreContext(context);
    while (*(volatile u16 *)0x04000280 & 0x8000) {
    }
}

}

// Knife_IrqStub (0x020c8100): empty interrupt stub
extern "C" void Knife_IrqStub(void);
ARM void Knife_IrqStub(void) {
}
