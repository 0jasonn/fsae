#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/os/dc_cache.h"
#include "sdk/wm/wm_system.h"

// WM_GetMPSendBufferSize() (0x0201f49c): size of the MP send buffer the current parent/child settings need (0 when WM
// is not in the parent or child state or the status says MP is not set up).
u32 WM_GetMPSendBufferSize(void) {
    WmWork *work = (WmWork *)WMi_GetWorkPointer();

    if (WMi_CheckStateEx(2, 7, 8) != 0) {
        return 0;
    }
    DC_InvalidateRange(&work->status->mpFlag, 4);
    if (work->status->mpFlag == 1) {
        return 0;
    }
    DC_InvalidateRange(&work->status->mpMaxSendSize, 4);
    return (work->status->mpMaxSendSize + 0x1f) & ~0x1f;
}

// WM_GetMPReceiveBufferSize() (0x0201f50c): size of the MP receive buffer: for a child a fixed formula of the packet
// size, for the parent (own AID 0) it also depends on the number of children. 0 outside the parent/child states.
u32 WM_GetMPReceiveBufferSize(void) {
    WmWork *work = (WmWork *)WMi_GetWorkPointer();
    u32 isParent;
    u32 packetSize;

    if (WMi_CheckStateEx(2, 7, 8) != 0) {
        return 0;
    }
    DC_InvalidateRange(&work->status->mpFlag, 4);
    if (work->status->mpFlag == 1) {
        return 0;
    }
    DC_InvalidateRange(&work->status->aid, 2);
    isParent = 1;
    if (work->status->aid != 0) {
        isParent = 0;
    }
    DC_InvalidateRange(&work->status->mpMaxRecvSize, 2);
    packetSize = work->status->mpMaxRecvSize;
    if (isParent != 1) {
        return ((packetSize + 0x51) & ~0x1f) << 1;
    }
    DC_InvalidateRange(&work->status->maxEntry, 2);
    return (((packetSize + 0xc) * work->status->maxEntry + 0x29) & ~0x1f) << 1;
}

// WM_GetAllowedChannel() (0x0201f5d8): bit mask of the channels the region allows (0x8000 before WM_Init, 0 when WM may
// not be enabled).
u16 WM_GetAllowedChannel(void) {
    if (WMi_CheckEnableFlag() == 0) {
        return 0;
    }
    if (WMi_CheckInitialized() != 0) {
        return 0x8000;
    }
    return *(volatile u16 *)0x02fffcfa;
}

// WM_GetLinkLevel() (0x0201f608): signal strength level of the current link; for a parent (state 9) 0 until a child
// is connected. 0 in the other states.
u16 WM_GetLinkLevel(void) {
    WmWork *work = (WmWork *)WMi_GetWorkPointer();

    if (WMi_CheckInitialized() != 0) {
        return 0;
    }
    DC_InvalidateRange(work->status, 2);
    switch (work->status->state) {
    case 9:
        DC_InvalidateRange(&work->status->mpReadyBitmap, 2);
        if (work->status->mpReadyBitmap == 0) {
            return 0;
        }
    case 10:
    case 11:
        DC_InvalidateRange(&work->status->linkLevel, 2);
        return work->status->linkLevel;
    default:
        return 0;
    }
}
