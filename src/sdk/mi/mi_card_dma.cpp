#include "engine/functions.h"
#include "sdk/mi/mi_dma.h"
#include "sdk/mi/mi_wram.h"
#include "sdk/mi/dma_conflict_api.h"

void MIi_CardDmaCopy32(u32 dmaNo, const void *src, void *dest, u32 size) {
    volatile u32 *control;

    Dma_CheckConflict(dmaNo, -1);
    Region_CheckNotIoOrRom(dmaNo, (u32)src, size, 0x1000000);
    if (size == 0) {
        return;
    }
    control = (volatile u32 *)(0x4000000 + (dmaNo * 3 + 2) * 4 + 0xb0);
    while (*control & 0x80000000) {
    }
    func_01ff8020(dmaNo, (u32)src, (u32)dest, 0xaf000001, 0);
}

void MI_Init(void) {
    MI_SetWramBank(3);
    func_02189338();
    MI_StopDma(0);
}
