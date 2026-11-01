#ifndef WIP_D_WM_D_H
#define WIP_D_WM_D_H

#include "global.h"
#include "types.h"

// REG_IME, the interrupt master enable. The WirelessManager functions save it, clear it and restore it by hand.
#define WM_REG_IME (*(volatile u16 *)0x04000208)

// Field of the WirelessManager at a byte offset from its start (self is the manager pointer).
#define WM_FIELD(self, off, type) (*(type *)((u8 *)(self) + (off)))

// The WirelessManager fields the wip units use, at their offsets from the start of the manager.
typedef struct WmDWork {
    u8 unk_0000[0x1d2];
    u16 bestChannel;        // 0x1d2: channel of the best measured level (MeasureChannel callback)
    u8 unk_1d4[0x1c5c - 0x1d4];
    u32 slots[16];          // 0x1c5c: 16 words
    void *allocator;        // 0x1c9c: WmAllocatorIface (non-NULL once initialized)
    u8 unk_1ca0[0x1ca8 - 0x1ca0];
    void *recvBuf;          // 0x1ca8
    void *sendBuf;          // 0x1cac
    u32 recvSize;           // 0x1cb0
    s32 sendSize;           // 0x1cb4
    u8 unk_1cb8;            // 0x1cb8
    u8 unk_1cb9;            // 0x1cb9
    u8 unk_1cba[0x1cbc - 0x1cba];
    s32 channel;            // 0x1cbc: channel index used by stepNextChannel
    s32 bestLevel;          // 0x1cc0: best measured level (MeasureChannel callback)
    s32 state;              // 0x1cc4
    u8 unk_1cc8[0x1ccc - 0x1cc8];
    u8 flag;                // 0x1ccc
    u8 unk_1ccd[0x1cce - 0x1ccd];
    u16 channelMask;        // 0x1cce: allowed channel bits (set by the enable callback)
    u8 unk_1cd0[0x1cd4 - 0x1cd0];
    s32 timer2;             // 0x1cd4
    s32 timer;              // 0x1cd8
    u8 unk_1cdc;            // 0x1cdc: controller flag (func_02090ecc)
    u8 unk_1cdd;            // 0x1cdd: frame flag
    u8 unk_1cde[0x1ce0 - 0x1cde];
    u16 linkValue;          // 0x1ce0
    u8 unk_1ce2[2];
    s32 connectPhase;        // 0x1ce4: connect phase (StartConnect and StartMP callbacks)
} WmDWork;

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
extern "C" s32 WM_StartDataSharing(void *buf, s32 kind, u16 mask, u16 param, s32 flag);
extern "C" void OS_Terminate(void);
extern "C" void Knife_Comm_WirelessManager_deleteMPBuffer(void *self);
extern "C" void Knife_Comm_WirelessManager_internalReset(void *self);

#endif
