#include "engine/functions.h"
#include "engine/oam_ring.h"
#include "sdk/gx/g2.h"
#include "sdk/mi/mi_dma.h"

void BgScr_CopyBG0(void *src, s32 offset, s32 size) {
    s32 dmaNo;
    void *dstBase;

    dstBase = G2S_GetBG0ScrPtr();
    dmaNo = OamRing_dmaNo;
    if (dmaNo != -1) {
        if ((u32)size > 0x1c) {
            if ((u32)dmaNo > 3) {
                if ((((u32)src | (u32)((u8 *)dstBase + offset) | (u32)size) & 3) == 0) {
                    DmaCopy32Fast((u32)(dmaNo - 4), src, (u8 *)dstBase + offset, size);
                } else {
                    MIi_CpuCopy16(src, (u8 *)dstBase + offset, size);
                }
                return;
            }
            MIi_DmaCopy16((u32)dmaNo, src, (u8 *)dstBase + offset, size, 1);
            return;
        }
    }
    MIi_CpuCopy16(src, (u8 *)dstBase + offset, size);
}

void BgScr_CopyBG1(void *src, s32 offset, s32 size) {
    s32 dmaNo;
    void *dstBase;

    dstBase = G2S_GetBG1ScrPtr();
    dmaNo = OamRing_dmaNo;
    if (dmaNo != -1) {
        if ((u32)size > 0x1c) {
            if ((u32)dmaNo > 3) {
                if ((((u32)src | (u32)((u8 *)dstBase + offset) | (u32)size) & 3) == 0) {
                    DmaCopy32Fast((u32)(dmaNo - 4), src, (u8 *)dstBase + offset, size);
                } else {
                    MIi_CpuCopy16(src, (u8 *)dstBase + offset, size);
                }
                return;
            }
            MIi_DmaCopy16((u32)dmaNo, src, (u8 *)dstBase + offset, size, 1);
            return;
        }
    }
    MIi_CpuCopy16(src, (u8 *)dstBase + offset, size);
}

void BgScr_CopyBG2(void *src, s32 offset, s32 size) {
    s32 dmaNo;
    void *dstBase;

    dstBase = G2S_GetBG2ScrPtr();
    dmaNo = OamRing_dmaNo;
    if (dmaNo != -1) {
        if ((u32)size > 0x1c) {
            if ((u32)dmaNo > 3) {
                if ((((u32)src | (u32)((u8 *)dstBase + offset) | (u32)size) & 3) == 0) {
                    DmaCopy32Fast((u32)(dmaNo - 4), src, (u8 *)dstBase + offset, size);
                } else {
                    MIi_CpuCopy16(src, (u8 *)dstBase + offset, size);
                }
                return;
            }
            MIi_DmaCopy16((u32)dmaNo, src, (u8 *)dstBase + offset, size, 1);
            return;
        }
    }
    MIi_CpuCopy16(src, (u8 *)dstBase + offset, size);
}

void BgScr_CopyBG3Alt(void *src, s32 offset, s32 size) {
    s32 dmaNo;
    void *dstBase;

    dstBase = G2_GetBG3ScrPtr();
    dmaNo = OamRing_dmaNo;
    if (dmaNo != -1) {
        if ((u32)size > 0x1c) {
            if ((u32)dmaNo > 3) {
                if ((((u32)src | (u32)((u8 *)dstBase + offset) | (u32)size) & 3) == 0) {
                    DmaCopy32Fast((u32)(dmaNo - 4), src, (u8 *)dstBase + offset, size);
                } else {
                    MIi_CpuCopy16(src, (u8 *)dstBase + offset, size);
                }
                return;
            }
            MIi_DmaCopy16((u32)dmaNo, src, (u8 *)dstBase + offset, size, 1);
            return;
        }
    }
    MIi_CpuCopy16(src, (u8 *)dstBase + offset, size);
}

void BgScr_CopyBG3(void *src, s32 offset, s32 size) {
    s32 dmaNo;
    void *dstBase;

    dstBase = G2S_GetBG3ScrPtr();
    dmaNo = OamRing_dmaNo;
    if (dmaNo != -1) {
        if ((u32)size > 0x1c) {
            if ((u32)dmaNo > 3) {
                if ((((u32)src | (u32)((u8 *)dstBase + offset) | (u32)size) & 3) == 0) {
                    DmaCopy32Fast((u32)(dmaNo - 4), src, (u8 *)dstBase + offset, size);
                } else {
                    MIi_CpuCopy16(src, (u8 *)dstBase + offset, size);
                }
                return;
            }
            MIi_DmaCopy16((u32)dmaNo, src, (u8 *)dstBase + offset, size, 1);
            return;
        }
    }
    MIi_CpuCopy16(src, (u8 *)dstBase + offset, size);
}

void BgChar_CopyBG0(void *src, s32 offset, s32 size) {
    s32 dmaNo;
    void *dstBase;

    dstBase = G2S_GetBG0CharPtr();
    dmaNo = OamRing_dmaNo;
    if (dmaNo != -1) {
        if ((u32)size > 0x30) {
            if ((u32)dmaNo > 3) {
                DmaCopy32Fast((u32)(dmaNo - 4), src, (u8 *)dstBase + offset, size);
                return;
            }
            MIi_DmaCopy32((u32)dmaNo, src, (u8 *)dstBase + offset, size, 1);
            return;
        }
    }
    MIi_CpuCopy32(src, (u8 *)dstBase + offset, size);
}

void BgChar_CopyBG1(void *src, s32 offset, s32 size) {
    s32 dmaNo;
    void *dstBase;

    dstBase = G2S_GetBG1CharPtr();
    dmaNo = OamRing_dmaNo;
    if (dmaNo != -1) {
        if ((u32)size > 0x30) {
            if ((u32)dmaNo > 3) {
                DmaCopy32Fast((u32)(dmaNo - 4), src, (u8 *)dstBase + offset, size);
                return;
            }
            MIi_DmaCopy32((u32)dmaNo, src, (u8 *)dstBase + offset, size, 1);
            return;
        }
    }
    MIi_CpuCopy32(src, (u8 *)dstBase + offset, size);
}

void BgChar_CopyBG2(void *src, s32 offset, s32 size) {
    s32 dmaNo;
    void *dstBase;

    dstBase = G2S_GetBG2CharPtr();
    dmaNo = OamRing_dmaNo;
    if (dmaNo != -1) {
        if ((u32)size > 0x30) {
            if ((u32)dmaNo > 3) {
                DmaCopy32Fast((u32)(dmaNo - 4), src, (u8 *)dstBase + offset, size);
                return;
            }
            MIi_DmaCopy32((u32)dmaNo, src, (u8 *)dstBase + offset, size, 1);
            return;
        }
    }
    MIi_CpuCopy32(src, (u8 *)dstBase + offset, size);
}

void BgChar_CopyBG3(void *src, s32 offset, s32 size) {
    s32 dmaNo;
    void *dstBase;

    dstBase = G2S_GetBG3CharPtr();
    dmaNo = OamRing_dmaNo;
    if (dmaNo != -1) {
        if ((u32)size > 0x30) {
            if ((u32)dmaNo > 3) {
                DmaCopy32Fast((u32)(dmaNo - 4), src, (u8 *)dstBase + offset, size);
                return;
            }
            MIi_DmaCopy32((u32)dmaNo, src, (u8 *)dstBase + offset, size, 1);
            return;
        }
    }
    MIi_CpuCopy32(src, (u8 *)dstBase + offset, size);
}
