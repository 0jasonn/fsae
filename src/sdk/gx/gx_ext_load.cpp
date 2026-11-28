#include "engine/functions.h"
#include "sdk/gx/gx_load.h"
#include "sdk/gx/gx_vramcnt.h"
#include "sdk/gx/vrambank_api.h"
#include "sdk/gx/vram_bank_bits_api.h"
#include "sdk/mi/mi_dma.h"
#include "sdk/mi/mi_memory.h"
#include "engine/oam_ring.h"

// Extended palette and texture upload helpers of the GX library: the Begin call maps the VRAM banks to the LCDC and
// records their address, the Load calls copy into them (by DMA when OamRing_dmaNo holds a channel), the End call waits
// for the copy and maps the banks back.

void GX_BeginLoadBGExtPltt(void) {
    s32 banks = Vram_ResetMainBankA();
    data_02129828.mainBgBanks = banks;
    switch (banks) {
    case 0:
        break;
    case 0x10:
        data_02129828.mainBgAddr = 0x6880000;
        data_02129828.mainBgOffset = 0;
        break;
    case 0x40:
        data_02129828.mainBgAddr = 0x6894000;
        data_02129828.mainBgOffset = 0x4000;
        break;
    case 0x20:
    case 0x60:
        data_02129828.mainBgAddr = 0x6890000;
        data_02129828.mainBgOffset = 0;
        break;
    }
}

void GX_LoadBGExtPltt(void *src, u32 offset, u32 size) {
    void *dst = (void *)(data_02129828.mainBgAddr + offset - data_02129828.mainBgOffset);
    s32 dmaNo = OamRing_dmaNo;
    if (dmaNo != -1) {
        if ((u32)dmaNo > 3) {
            DmaCopy32AsyncFast((u32)(dmaNo - 4), src, dst, size, 0, 0);
            return;
        }
        MIi_DmaCopy32Async((u32)dmaNo, src, dst, size, 0, 0, 1);
        return;
    }
    MIi_CpuCopy32(src, dst, size);
}

void GX_EndLoadBGExtPltt(void) {
    s32 dmaNo = OamRing_dmaNo;
    if (dmaNo != -1) {
        if ((u32)dmaNo > 3) {
            DmaWaitFast((u32)(dmaNo - 4));
        } else {
            MI_WaitDma((u32)dmaNo);
        }
    }
    func_02014c24((s32)data_02129828.mainBgBanks);
    data_02129828.mainBgOffset = data_02129828.mainBgAddr = data_02129828.mainBgBanks = 0;
}

void GX_BeginLoadOBJExtPltt(void) {
    s32 banks = Vram_ResetMainBankB();
    data_02129828.mainObjBanks = banks;
    switch (banks) {
    case 0:
        break;
    case 0x20:
        data_02129828.mainObjAddr = 0x6890000;
        break;
    case 0x40:
        data_02129828.mainObjAddr = 0x6894000;
        break;
    }
}

void GX_LoadOBJExtPltt(void *src, u32 offset, u32 size) {
    u32 base = data_02129828.mainObjAddr;
    s32 dmaNo = OamRing_dmaNo;
    if (dmaNo != -1) {
        if ((u32)dmaNo > 3) {
            DmaCopy32AsyncFast((u32)(dmaNo - 4), src, (void *)(base + offset), size, 0, 0);
            return;
        }
        MIi_DmaCopy32Async((u32)dmaNo, src, (void *)(base + offset), size, 0, 0, 1);
        return;
    }
    MIi_CpuCopy32(src, (void *)(base + offset), size);
}

void GX_EndLoadOBJExtPltt(void) {
    s32 dmaNo = OamRing_dmaNo;
    if (dmaNo != -1) {
        if ((u32)dmaNo > 3) {
            DmaWaitFast((u32)(dmaNo - 4));
        } else {
            MI_WaitDma((u32)dmaNo);
        }
    }
    GX_SetBankForOBJExtPltt(data_02129828.mainObjBanks);
    data_02129828.mainObjAddr = data_02129828.mainObjBanks = 0;
}

void GXS_BeginLoadBGExtPltt(void) {
    data_02129828.subBgBanks = Vram_ResetSubBankA();
}

void GXS_LoadBGExtPltt(void *src, u32 offset, u32 size) {
    s32 dmaNo = OamRing_dmaNo;
    if (dmaNo != -1) {
        if ((u32)dmaNo > 3) {
            DmaCopy32AsyncFast((u32)(dmaNo - 4), src, (void *)(0x6898000 + offset), size, 0, 0);
            return;
        }
        MIi_DmaCopy32Async((u32)dmaNo, src, (void *)(0x6898000 + offset), size, 0, 0, 1);
        return;
    }
    MIi_CpuCopy32(src, (void *)(0x6898000 + offset), size);
}

void GXS_EndLoadBGExtPltt(void) {
    s32 dmaNo = OamRing_dmaNo;
    if (dmaNo != -1) {
        if ((u32)dmaNo > 3) {
            DmaWaitFast((u32)(dmaNo - 4));
        } else {
            MI_WaitDma((u32)dmaNo);
        }
    }
    Vram_SetBankGroupB(data_02129828.subBgBanks);
    data_02129828.subBgBanks = 0;
}

void GXS_BeginLoadOBJExtPltt(void) {
    data_02129828.subObjBanks = Vram_ResetSubBankB();
}

void GXS_LoadOBJExtPltt(void *src, u32 offset, u32 size) {
    s32 dmaNo = OamRing_dmaNo;
    if (dmaNo != -1) {
        if ((u32)dmaNo > 3) {
            DmaCopy32AsyncFast((u32)(dmaNo - 4), src, (void *)(0x68a0000 + offset), size, 0, 0);
            return;
        }
        MIi_DmaCopy32Async((u32)dmaNo, src, (void *)(0x68a0000 + offset), size, 0, 0, 1);
        return;
    }
    MIi_CpuCopy32(src, (void *)(0x68a0000 + offset), size);
}

void GXS_EndLoadOBJExtPltt(void) {
    s32 dmaNo = OamRing_dmaNo;
    if (dmaNo != -1) {
        if ((u32)dmaNo > 3) {
            DmaWaitFast((u32)(dmaNo - 4));
        } else {
            MI_WaitDma((u32)dmaNo);
        }
    }
    Vram_SetBankGroupC(data_02129828.subObjBanks);
    data_02129828.subObjBanks = 0;
}
