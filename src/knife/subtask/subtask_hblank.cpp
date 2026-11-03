#include "engine/functions.h"
#include "global.h"
#include "knife/subtask/subtask_hblank.h"

// HBlank interrupt handler of the subtask code: reads VCOUNT, then sets bit 1 of the flag word at 0x02fe3ff8.
// 0x0209a890 subtask_hblank_irq -> subtask_hblank_irq

void subtask_hblank_irq(void) {
    u32 base = (u32)data_02fe0000 + 0x3000;
    u16 vcount;

    vcount = *(volatile u16 *)0x04000006;
    *(volatile u32 *)(base + 0xff8) |= 2;
}
