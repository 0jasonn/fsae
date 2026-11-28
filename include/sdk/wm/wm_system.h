#ifndef SDK_WM_WM_SYSTEM_H
#define SDK_WM_WM_SYSTEM_H

// TwlSDK WM library system part (wm_system.c): the library state, the per-command callback table and the state checks.
#include "types.h"

typedef void (*WmCallback)(void *result);

// Status block shared with the ARM7 (read after DC_InvalidateRange; TwlSDK WMStatus).
typedef struct WmStatusBlock {
    u16 state;           // 0x000: current WM state (0 = ready, 1 = stop, 2 = idle, ...)
    u8 unk_02[0x0a];     // 0x002
    u32 mpFlag;          // 0x00c: 1 while MP is running (the buffer size queries then report 0)
    u8 unk_10[0x2c];     // 0x010
    u16 mpMaxSendSize;   // 0x03c
    u16 mpMaxRecvSize;   // 0x03e
    u8 unk_40[0x3c];     // 0x040
    void *mpSendBuf;     // 0x07c: data being sent (WM_SetMPDataToPortEx refuses it again)
    u8 unk_80[0x86 - 0x80];
    u16 unk_86;          // 0x086: invalidated before sending (child)
    u8 unk_88[0x34];     // 0x088
    u16 linkLevel;       // 0x0bc: signal strength level of the current link
    u8 unk_be[0x3a];     // 0x0be
    u16 maxEntry;        // 0x0f8: maximum number of children of the parent parameters
    u8 unk_fa[0x182 - 0xfa];
    u16 mpReadyBitmap;   // 0x182: child: nonzero once the parent's MP is ready (name is a guess)
    u8 unk_184[0x188 - 0x184];
    u16 aid;             // 0x188: own AID, 0 = parent (name is a guess)
} WmStatusBlock;

// Work area owned by the WM library (handed to WM_Init by the caller; TwlSDK WMArm9Buf).
typedef struct WmWork {
    u32 *arm7Buf;                       // 0x000: ARM7 part of the work area (work + 0x200)
    WmStatusBlock *status;              // 0x004: arm7Buf + 0x300
    u32 unk_08;                         // 0x008
    u32 *fifo9to7;                      // 0x00c: status + 0x800
    u32 *fifo7to9;                      // 0x010: fifo9to7 + 0x100
    u16 dmaNo;                          // 0x014
    u16 unk_16;                         // 0x016: cleared by WM_Init
    WmCallback callbackTable[0x2d];     // 0x018: per-command callbacks
    WmCallback portCallbackTable[16];   // 0x0cc: per-port receive callbacks
    void *portCallbackArgument[16];     // 0x10c
    u32 connectedAids;                  // 0x14c
    u16 aid;                            // 0x150
} WmWork;

// One 0x100-byte command block shared with the ARM7 (the first halfword is the command id; bit 15 = block is free).
typedef struct WmCommandBuffer {
    u16 command;      // 0x00
    u16 pad_02;       // 0x02
    u32 argument[63]; // 0x04
} WmCommandBuffer;

// WM library state at data_0212b960 (0x18 bytes).
typedef struct WmState {
    u16 initialized;             // 0x00
    u16 pad_02;                  // 0x02
    WmWork *work;                // 0x04
    void (*sleepCallback)(void); // 0x08: 0x10-byte callback record handed to the PM list (dsd: data_0212b968)
    u32 sleepCallbackArg;        // 0x0c
    u8 unk_10[8];                // 0x10
} WmState;

extern WmState data_0212b960;
extern struct OsMessageQueue data_0212b978; // queue of free command blocks (sdk/os/os_message.h)
extern void *data_0212b998[10];             // storage of that queue
extern WmCommandBuffer data_0212ba20[10];   // the command blocks
extern u32 data_020f24c0; // next TGID: seeded from the RTC on first use (0x10000 means not seeded), then counts up

extern "C" {
int WM_Init(void *sysWork, u32 dmaNo);
s32 WM_CheckInitialized(void); // src/sdk/wm/wm_cmd.cpp: wrapper of NWMi_CheckInitialized
s32 WM_Finish(void);
void *WmGetCommandBuffer4Arm7(void);
u32 WMi_SendCommand(u32 command, u16 wordCount, ...);
u32 WMi_SendCommandDirect(u16 *data, u32 size);
void WMi_SetCallbackTable(u32 id, WmCallback callback);
void *WMi_GetWorkPointer(void);
s32 WMi_CheckInitialized(void);
s32 WMi_CheckIdle(void);
s32 WMi_CheckStateEx(s32 count, ...);
void WmClearFifoRecvFlag(void);
u16 WM_GetAID(void);
u16 WM_GetConnectedAIDs(void);
s32 WMi_CheckEnableFlag(void);
u32 WM_GetMPSendBufferSize(void);
u32 WM_GetMPReceiveBufferSize(void);
u16 WM_GetAllowedChannel(void);
u16 WM_GetLinkLevel(void);
u16 WM_GetDispersionBeaconPeriod(void);
s32 WM_GetDispersionScanPeriod(void);
u16 WM_GetNextTgid(void);

// Not decompiled yet.
s32 WmInitCore(void *work, u32 dmaNo, u32 size);
void func_0201eedc(u32 tag, u32 data, s32 err); // PXI receive callback of WM (tag 10)
}

#endif
