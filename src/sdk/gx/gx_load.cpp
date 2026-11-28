#include "engine/functions.h"
#include "engine/oam_ring.h"
#include "sdk/gx/gx_load.h"
#include "sdk/mi/mi_dma.h"

// GX_Load*: copy palette/OAM/OBJ data into the engine A (GX_) or B (GXS_) VRAM, by DMA when OamRing_dmaNo holds a channel.

void GX_LoadBGPltt(void *src, s32 offset, s32 size) {
    s32 dmaNo;
    dmaNo = OamRing_dmaNo;
    if (dmaNo != -1) {
        if ((u32)size > 28) {
            if ((u32)dmaNo > 3) {
                if ((((u32)src | (u32)(void *)(0x5000000 + offset) | (u32)size) & 3) == 0) {
                    DmaCopy32Fast((u32)(dmaNo - 4), src, (void *)(0x5000000 + offset), size);
                } else {
                    MIi_CpuCopy16(src, (void *)(0x5000000 + offset), size);
                }
                return;
            }
            MIi_DmaCopy16((u32)dmaNo, src, (void *)(0x5000000 + offset), size, 1);
            return;
        }
    }
    MIi_CpuCopy16(src, (void *)(0x5000000 + offset), size);
}

void GXS_LoadBGPltt(void *src, s32 offset, s32 size) {
    s32 dmaNo;
    dmaNo = OamRing_dmaNo;
    if (dmaNo != -1) {
        if ((u32)size > 28) {
            if ((u32)dmaNo > 3) {
                if ((((u32)src | (u32)(void *)(0x5000400 + offset) | (u32)size) & 3) == 0) {
                    DmaCopy32Fast((u32)(dmaNo - 4), src, (void *)(0x5000400 + offset), size);
                } else {
                    MIi_CpuCopy16(src, (void *)(0x5000400 + offset), size);
                }
                return;
            }
            MIi_DmaCopy16((u32)dmaNo, src, (void *)(0x5000400 + offset), size, 1);
            return;
        }
    }
    MIi_CpuCopy16(src, (void *)(0x5000400 + offset), size);
}

void GX_LoadOBJPltt(void *src, s32 offset, s32 size) {
    s32 dmaNo;
    dmaNo = OamRing_dmaNo;
    if (dmaNo != -1) {
        if ((u32)size > 28) {
            if ((u32)dmaNo > 3) {
                if ((((u32)src | (u32)(void *)(0x5000200 + offset) | (u32)size) & 3) == 0) {
                    DmaCopy32Fast((u32)(dmaNo - 4), src, (void *)(0x5000200 + offset), size);
                } else {
                    MIi_CpuCopy16(src, (void *)(0x5000200 + offset), size);
                }
                return;
            }
            MIi_DmaCopy16((u32)dmaNo, src, (void *)(0x5000200 + offset), size, 1);
            return;
        }
    }
    MIi_CpuCopy16(src, (void *)(0x5000200 + offset), size);
}

void GXS_LoadOBJPltt(void *src, s32 offset, s32 size) {
    s32 dmaNo;
    dmaNo = OamRing_dmaNo;
    if (dmaNo != -1) {
        if ((u32)size > 28) {
            if ((u32)dmaNo > 3) {
                if ((((u32)src | (u32)(void *)(0x5000600 + offset) | (u32)size) & 3) == 0) {
                    DmaCopy32Fast((u32)(dmaNo - 4), src, (void *)(0x5000600 + offset), size);
                } else {
                    MIi_CpuCopy16(src, (void *)(0x5000600 + offset), size);
                }
                return;
            }
            MIi_DmaCopy16((u32)dmaNo, src, (void *)(0x5000600 + offset), size, 1);
            return;
        }
    }
    MIi_CpuCopy16(src, (void *)(0x5000600 + offset), size);
}

void GX_LoadOAM(const void *src, u32 offset, u32 size) {
    s32 dmaNo;
    void *dst;

    dst = (void *)(0x7000000 + offset);
    dmaNo = OamRing_dmaNo;
    if (dmaNo != -1) {
        if ((u32)size > 48) {
            if ((u32)dmaNo > 3) {
                DmaCopy32Fast((u32)(dmaNo - 4), src, dst, size);
                return;
            }
            MIi_DmaCopy32((u32)dmaNo, src, dst, size, 1);
            return;
        }
    }
    MIi_CpuCopy32(src, dst, size);
}

void GXS_LoadOAM(const void *src, u32 offset, u32 size) {
    s32 dmaNo;

    dmaNo = OamRing_dmaNo;
    if (dmaNo != -1) {
        if ((u32)size > 48) {
            if ((u32)dmaNo > 3) {
                DmaCopy32Fast((u32)(dmaNo - 4), src, (void *)(0x7000400 + offset), size);
                return;
            }
            MIi_DmaCopy32((u32)dmaNo, src, (void *)(0x7000400 + offset), size, 1);
            return;
        }
    }
    MIi_CpuCopy32(src, (void *)(0x7000400 + offset), size);
}

void GX_LoadOBJ(void *src, s32 offset, s32 size) {
    s32 dmaNo;
    void *dst;

    dst = (void *)(0x6400000 + offset);
    dmaNo = OamRing_dmaNo;
    if (dmaNo != -1) {
        if ((u32)size > 48) {
            if ((u32)dmaNo > 3) {
                DmaCopy32Fast((u32)(dmaNo - 4), src, dst, size);
                return;
            }
            MIi_DmaCopy32((u32)dmaNo, src, dst, size, 1);
            return;
        }
    }
    MIi_CpuCopy32(src, dst, size);
}

void GXS_LoadOBJ(void *src, s32 offset, s32 size) {
    s32 dmaNo;
    void *dst;

    dst = (void *)(0x6600000 + offset);
    dmaNo = OamRing_dmaNo;
    if (dmaNo != -1) {
        if ((u32)size > 48) {
            if ((u32)dmaNo > 3) {
                DmaCopy32Fast((u32)(dmaNo - 4), src, dst, size);
                return;
            }
            MIi_DmaCopy32((u32)dmaNo, src, dst, size, 1);
            return;
        }
    }
    MIi_CpuCopy32(src, dst, size);
}
