#include "engine/functions.h"
#include "sdk/gx/gx_load.h"
#include "sdk/gx/gx_vramcnt.h"
#include "sdk/gx/vrambank_api.h"
#include "sdk/mi/mi_dma.h"
#include "sdk/mi/mi_memory.h"
#include "engine/oam_ring.h"

// Texture and texture palette upload helpers of the GX library (same scheme as the extended palette helpers).

void GX_LoadTex(void *src, u32 offset, u32 size) {
    u32 addr2 = data_02129844.texAddr2;
    u32 dst;
    u32 firstSize;
    u32 base;
    s32 dmaNo;

    if (addr2 == 0) {
        dst = data_02129844.texAddr + offset;
    } else if (offset + size < data_02129844.texSplitSize) {
        dst = data_02129844.texAddr + offset;
    } else if (offset >= data_02129844.texSplitSize) {
        dst = addr2 + offset - data_02129844.texSplitSize;
    } else {
        firstSize = data_02129844.texSplitSize - offset;
        base = data_02129844.texAddr;
        dmaNo = OamRing_dmaNo;
        if (dmaNo != -1 && firstSize > 0x30) {
            if ((u32)dmaNo > 3) {
                DmaCopy32Fast((u32)(dmaNo - 4), src, (void *)(base + offset), firstSize);
            } else {
                MIi_DmaCopy32((u32)dmaNo, src, (void *)(base + offset), firstSize, 1);
            }
        } else {
            MIi_CpuCopy32(src, (void *)(base + offset), firstSize);
        }
        dmaNo = OamRing_dmaNo;
        if (dmaNo != -1) {
            if ((u32)dmaNo > 3) {
                DmaCopy32AsyncFast((u32)(dmaNo - 4), (u8 *)src + firstSize, (void *)addr2, size - firstSize, 0, 0);
                return;
            }
            MIi_DmaCopy32Async((u32)dmaNo, (u8 *)src + firstSize, (void *)addr2, size - firstSize, 0, 0, 1);
            return;
        }
        MIi_CpuCopy32((u8 *)src + firstSize, (void *)addr2, size - firstSize);
        return;
    }
    dmaNo = OamRing_dmaNo;
    if (dmaNo != -1) {
        if ((u32)dmaNo > 3) {
            DmaCopy32AsyncFast((u32)(dmaNo - 4), src, (void *)dst, size, 0, 0);
            return;
        }
        MIi_DmaCopy32Async((u32)dmaNo, src, (void *)dst, size, 0, 0, 1);
        return;
    }
    MIi_CpuCopy32(src, (void *)dst, size);
}

void GX_EndLoadTex(void) {
    s32 dmaNo = OamRing_dmaNo;
    if (dmaNo != -1) {
        if ((u32)dmaNo > 3) {
            DmaWaitFast((u32)(dmaNo - 4));
        } else {
            MI_WaitDma((u32)dmaNo);
        }
    }
    func_02014db8(data_02129844.texBanks);
    data_02129844.texBanks = data_02129844.texAddr = data_02129844.texAddr2 = data_02129844.texSplitSize = 0;
}

void GX_BeginLoadTexPltt(void) {
    s32 banks = Vram_ResetBankD();
    data_02129844.texPlttBanks = banks;
    data_02129844.texPlttAddr = data_020cd1fc[banks >> 4] << 12;
}

void GX_LoadTexPltt(void *src, u32 offset, u32 size) {
    u32 base = data_02129844.texPlttAddr;
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

void GX_EndLoadTexPltt(void) {
    s32 dmaNo = OamRing_dmaNo;
    if (dmaNo != -1) {
        if ((u32)dmaNo > 3) {
            DmaWaitFast((u32)(dmaNo - 4));
        } else {
            MI_WaitDma((u32)dmaNo);
        }
    }
    func_02014f30(data_02129844.texPlttBanks);
    data_02129844.texPlttAddr = data_02129844.texPlttBanks = 0;
}
