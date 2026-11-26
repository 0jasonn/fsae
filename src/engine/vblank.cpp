#include "engine/functions.h"
#include "engine/vblank.h"
#include "global.h"
#include "sdk/os/cp_context.h"

// VBlankIntr (0x02049a94): per-frame VBlank work. Uploads the pending screen buffer, runs the resource, display and
// character transfers, the subtask hook and the HBlank DMA restart, then raises the IRQ check flag in the shared block.
void VBlankIntr(void) {
    u8 context[0x1c];
    u32 index;
    u32 *shared;

    CP_SaveContext(context);
    MultiSioVSync();
    func_0208d5d4();
    if (frameState.transferLock == 0 && data_0212c4e0 != 0) {
        index = data_0212c4c8 ^ 1;
        if (data_021348f4[index] != 0) {
            data_021348f4[index] = 0;
            MIi_CpuCopyFast(data_0213cfa0 + (index << 13), (void *)(0x06000000 + ((data_02158fa0.disp->cnt & 0x1f00) << 3)), 0x2000);
        }
        ResourceCtrl();
        DispCtrlSet();
        func_02080ca4();
        CgTrans();
        CgSubTrans();
        data_0212c4e0 = 0;
    }
    subtask_vblank();
    if (hblankDma.enabled != 0) {
        MI_StopDma(0);
        MI_HBlankDmaCopy16(0, hblankDma.src, hblankDma.dst, 2);
    }
    shared = (u32 *)0x02fe0000;
    shared += 0xc00;
    *(vu16 *)0x04000208;
    *(vu16 *)0x04000208 = 0;
    shared[0x3fe] |= 1;
    *(vu16 *)0x04000208;
    *(vu16 *)0x04000208 = 1;
    CPi_RestoreContext(context);
    while (*(vu16 *)0x04000280 & 0x8000) {
    }
}
