#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/wm_d.h"

// WirelessManager::allocMPBuffer (0x0209244c, invented name): frees the buffers, then allocates the send buffer (size from
// WM_GetMPSendBufferSize, at most 0x200) and the receive buffer (at most 0x400), both aligned to 0x20. FALSE on any failure
// (buffers freed again, OS_Terminate on an allocation failure).
extern "C" BOOL Knife_Comm_WirelessManager_allocMPBuffer(void *self);
ARM BOOL Knife_Comm_WirelessManager_allocMPBuffer(void *self) {
    WmDWork *wm;
    WmAllocatorIface *allocator;
    u32 size;

    wm = (WmDWork *)self;
    Knife_Comm_WirelessManager_deleteMPBuffer(self);
    size = WM_GetMPSendBufferSize();
    wm->sendSize = size;
    if (size == 0 || size > 0x200) {
        Knife_Comm_WirelessManager_deleteMPBuffer(self);
        return 0;
    }
    allocator = (WmAllocatorIface *)wm->allocator;
    wm->sendBuf = allocator->allocate(size, 0x20);
    if (wm->sendBuf == NULL) {
        OS_Terminate();
        Knife_Comm_WirelessManager_deleteMPBuffer(self);
        return 0;
    }
    size = WM_GetMPReceiveBufferSize();
    wm->recvSize = size;
    if (size == 0 || size > 0x400) {
        Knife_Comm_WirelessManager_deleteMPBuffer(self);
        return 0;
    }
    allocator = (WmAllocatorIface *)wm->allocator;
    wm->recvBuf = allocator->allocate(size, 0x20);
    if (wm->recvBuf != NULL) {
        return 1;
    }
    OS_Terminate();
    Knife_Comm_WirelessManager_deleteMPBuffer(self);
    return 0;
}

// WirelessManager::deleteMPBuffer (0x02092528): frees the send and receive buffers through the allocator (slot 1) and
// clears their pointers and sizes.
extern "C" void Knife_Comm_WirelessManager_deleteMPBuffer(void *self);
ARM void Knife_Comm_WirelessManager_deleteMPBuffer(void *self) {
    WmDWork *wm;
    void *recv;

    wm = (WmDWork *)self;
    if (wm->sendBuf != NULL) {
        ((WmAllocatorIface *)wm->allocator)->deallocate(wm->sendBuf);
    }
    recv = wm->recvBuf;
    wm->sendBuf = NULL;
    wm->sendSize = 0;
    if (recv != NULL) {
        ((WmAllocatorIface *)wm->allocator)->deallocate(recv);
    }
    wm->recvBuf = NULL;
    wm->recvSize = 0;
}
