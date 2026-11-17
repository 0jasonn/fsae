#ifndef KNIFE_COMM_WM_WORK_H
#define KNIFE_COMM_WM_WORK_H

#include "global.h"
#include "types.h"
#include "knife/comm/wireless_manager.h"

// REG_IME, the interrupt master enable. The WirelessManager functions save it, clear it and restore it by hand.
#define WM_REG_IME (*(volatile u16 *)0x04000208)

// Field of the WirelessManager at a byte offset from its start (self is the manager pointer).
#define WM_FIELD(self, off, type) (*(type *)((u8 *)(self) + (off)))


// Header of the SDK callback result (WMCallback): the API id, then the error code at offset 2.
typedef struct WmCallbackHead {
    u16 apiId;
    u16 errCode;
} WmCallbackHead;

// SDK measure-channel callback result: the channel and its level at offsets 8 and 0xa.
typedef struct WmMeasureResult {
    u16 apiId;
    u16 errCode;
    u8 unk_4[4];
    u16 channel;
    u16 level;
} WmMeasureResult;

// Allocator the manager is initialized with: slot 0 allocates, slot 1 frees. Pure virtual, so no vtable is emitted.
class WmAllocatorIface {
public:
    virtual void *allocate(u32 size, u32 align) = 0;
    virtual void deallocate(void *block) = 0;
};

// SDK and ROM functions the wip WirelessManager code calls.
extern "C" u32 WM_GetMPSendBufferSize(void);
extern "C" u32 WM_GetMPReceiveBufferSize(void);
extern "C" u16 WM_GetAllowedChannel(void);
extern "C" BOOL Knife_Comm_WirelessManager_checkCallbackResult(void *self, void *result);
extern "C" void Knife_Comm_WirelessManager_appendScanResult(void *self, void *bssDesc, s32 linkLevel);
extern "C" BOOL Knife_Comm_WirelessManager_handleResult(void *self, s32 code, s32 flag, const char *name);
extern "C" void OS_Terminate(void);
extern "C" void Knife_Comm_WirelessManager_deleteMPBuffer(void *self);
extern "C" BOOL Knife_Comm_WirelessManager_internalReset(void *self);

#endif
