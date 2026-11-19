#include "engine/functions.h"
#include "engine/disp_reset.h"
#include "engine/irq.h"

// DispReset (0x0202a60c): resets the display state: clears the display control register, the buffers that are copied
// to OAM, palette and VRAM, and stops the HBlank DMA when it is running.
void DispReset(void) {
    u32 *dispcnt = (u32 *)0x04000000;
    u8 zero = 0;

    *dispcnt = ConvertDispCntToTWL(zero, *dispcnt);
    data_0212c4e0 = zero;
    data_0212c4c8 = zero;
    data_0212c56c = (u32)data_0212ccb0;
    data_0212c570 = (u32)data_0212cdb0;
    data_0212c528 = (u32)data_0212de50;
    data_0212c594.unk_05 = zero;
    data_0212c594.unk_04 = zero;
    DispCtrlClear();
    MIi_CpuClearFast(0xc0, (void *)0x07000000, 0x400);
    MIi_CpuClearFast(0xc0, objAffineSet, 0x800);
    MIi_CpuClearFast(zero, data_0212ccb0, 0x200);
    MIi_CpuClearFast(zero, data_021361a0, 0x1000);
    if (hblankDma.enabled != 0) {
        MI_StopDma(zero);
        hblankDma.enabled = zero;
    }
}
